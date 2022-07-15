#ifndef ASHISH_big_int_H_
#define ASHISH_big_int_H_

#include <bits/stdc++.h>
using namespace std;
#define ll long long

class big_int{
private:
  vector<ll> num;
  bool positive=true;
  static const ll base=1000000000;
public:
  // Constructor//
  big_int(){
    positive=true;
  }

  big_int(const big_int &b)
        : num(b.num),
          positive(b.positive){}
    big_int(long long value){
      if (value < 0) {
          positive = false;
          value *= -1;
      } else {
          positive = true;
      }

      while (value) {
          num.push_back((int) (value % base));
          value /= base;
      }
  }
  big_int(string str){
      int size = str.length();

      positive = (str[0] != '-');
      if(str[0]=='-'){
        str.erase(str.begin());
      }
      while (true) {
          if (size <= 0) break;
          if (!positive && size <= 1) break;

          int length = 0;
          int tp = 0;
          int prefix = 1;
          for (int i(size - 1); i>=max(size-9,0) ;i--) {
              tp += (str[i] - '0') * prefix;
              prefix *= 10;
              ++length;
          }
          num.push_back(tp);
          size -= length;
      }
  }
  // Assign//
  big_int operator=(const big_int &x){
    num.clear();
    for(auto ch:x.num){
      num.push_back(ch);
    }
    return *this;
  }
  big_int operator=(ll b){
    big_int tb(b);
    num.clear();
    for(auto ch:tb.num){
      num.push_back(ch);
    }
    return *this;
  }
  // output//
  void print(){
    int len=num.size();
    if(len==1 and num[0]==0){
      cout<<"0\n";
      return;
    }
    if(!positive){
      cout<<'-';
    }
    for(int i=len-1;i>=0;i--){
      cout<<num[i];
    }
    cout<<"\n";
  }
  //Clear//
  void clear(){
    num.clear();
    positive=true;
  }
  // Comparison//
  int check (const big_int &a,const big_int &b){
    if(a.positive and !b.positive){
      return 0;
    }
    if(!a.positive and b.positive){
      return 1;
    }

    if(a.num.size()>b.num.size())return(0);
    if(a.num.size()<b.num.size())return(1);
    int l1=min(a.num.size(),b.num.size());
    for(int i=l1-1;i>=0;i--){
      if(a.num[i]<b.num[i]){ if(a.positive) return(1); else return(0);};
      if(b.num[i]<a.num[i]){if(a.positive) return(0); else return(1);};
    }
    return 2;
  }
  bool operator < (const big_int &b){ return(check(*this,b)==1);}
  bool operator > (const big_int &b){ return(check(*this,b)==0);}
  bool operator <=(const big_int &b){ return(check(*this,b)>=1);}
  bool operator >=(const big_int &b){ return(check(*this,b)%2==0);}
  bool operator !=(const big_int &b){ return(check(*this,b)!=2);}
  bool operator ==(const big_int &b){ return(check(*this,b)==2);}

  // Addition//
  big_int operator +(const big_int &b){
    if(!b.positive){
      return *this-b;
    }
    big_int temp;
    int s1=num.size(),s2=b.num.size();
    int l=max(num.size(),b.num.size());
    bool amlarge=(s1>s2);
    for(int i=0;i<l;++i){
      if(amlarge){
        if(i>=s2){
          temp.num.push_back(num[i]);
        }else{
          temp.num.push_back(num[i]+b.num[i]);
        }
      }else{
        if(i>=s1){
          temp.num.push_back(b.num[i]);
        }else{
          temp.num.push_back(num[i]+b.num[i]);
        }
      }
    }
    temp.num.push_back(0);
    for(int i=0;i<l;++i) {
      temp.num[i+1]+=temp.num[i]/base;
      temp.num[i]%=base;
    }
    if(temp.num.back()==0){
      temp.num.pop_back();
    }
    return temp;
  }
  big_int operator +(ll b){
    if(b<0){
      return *this-b;
    }
    big_int temp(b);
    return (*this+temp);
  }

  //Subtraction//
  big_int operator -(const big_int &b){
    if(!b.positive){
      return *this+b;
    }
    big_int temp;
    int s1=num.size(),s2=b.num.size();
    int l=max(num.size(),b.num.size());
    bool amlarge=(s1>s2);
    for(int i=0;i<s1;++i){
      if(amlarge){
        if(i>=s2){
          temp.num.push_back(num[i]);
        }else{
          temp.num.push_back(num[i]-b.num[i]);
        }
      }else{
        if(i>=s1){
          temp.num.push_back(-1*b.num[i]);
        }else{
          temp.num.push_back(num[i]-b.num[i]);
        }
      }
    }
    temp.num.push_back(0);
    for(int i=0;i<s1;++i){
      if(temp.num[i]<0){
        temp.num[i]+=base;
        temp.num[i+1]--;
      }
    }
    while(temp.num[temp.num.size()-1]==0&&temp.num.size()>1)temp.num.pop_back();
    return temp;
  }
  big_int operator -(ll b){
    if(b<0){
      return *this+b;
    }
    big_int temp(b);
    return (*this-temp);
  }

  //Multiplication//
  big_int operator *(const big_int &b){
    int i,j;
    int tot=num.size()+b.num.size();
    vector<ll> tmp(tot+1,0);
    for(i=0;i<num.size();++i){
      if(num[i]!=0)
      for(j=0;j<b.num.size();++j)if(b.num[j]!=0){
        tmp[i+j]+=num[i]*b.num[j];
        tmp[i+j+1]+=tmp[i+j]/base;
        tmp[i+j]%=base;
      }
    }
    while(tmp[tmp.size()-1]==0 and tmp.size()>1) tmp.pop_back();
    big_int temp;
    temp.num=tmp;
    if((positive and !b.positive) or(!positive and b.positive)){
      temp.positive=false;
    }else{
      temp.positive=true;
    }
    return temp;
  }
  big_int operator *(ll b){
    big_int temp(b);
    return (*this*temp);
  }

  big_int operator +=(const big_int &b){return *this=(*this+b);}
  big_int operator *=(const big_int &b){return *this=(*this*b);}
  big_int operator -=(const big_int &b){return *this=(*this -b);}
  big_int operator *=(ll x) {return( *this=(*this *x));}
  big_int operator +=(ll x) {return( *this=(*this +x));}
  big_int operator -=(ll x) {return( *this=(*this -x));}

  //power//
  big_int power(ll b){
      big_int res(1);
      ll save=b;
      while (b > 0) {
          if (b & 1)
              res = res * (*this);
          *(this)*= *(this);
          b >>= 1;
      }
      if(!positive and b%2==0){
        positive=true;
      }
      return res;
  }

};

//Factorial//
big_int factorial(ll n){
  big_int res = 1;
    for(ll i=2;i<=n;i++){
      res*=i;
    }
    return res;
}

#endif