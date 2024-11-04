#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <memory>
#define pi 3.14
using namespace std;
// forward declarations
class calculatorsystem;
// ==================== shape calculator ====================
class shapecalculator {
    float a,s1,s2,s3,r;
    int choice;
    string shape;
public:
    shapecalculator():a(0),s1(0),s2(0),s3(0),r(0),choice(0) {}
    float area(float s1,float s2) {
        return s1*s2;
    }
    float area(float s1) {
        return s1*s1;
    }
    float area(float s1,float s2,float s3) {
        float s=(s1+s2+s3)/2;
        return sqrt(s*(s-s1)*(s-s2)*(s-s3));
    }
    float areas(float r) {
        return pi*r*r;
    }
    void calculate() {
        cout<<"\n=== shape calculator ===\n";
        cout<<"1. rectangle\n2. square\n3. triangle\n4. circle\n";
        cout<<"enter choice:";
        cin>>choice;
        switch(choice) {
            case 1:
                shape="rectangle";
                cout<<"enter length and width:";
                cin>>s1>>s2;
                cout<<"area:"<<area(s1,s2)<<endl;
                break;
            case 2:
                shape="square";
                cout<<"enter side:";
                cin>>s1;
                cout<<"area:"<<area(s1)<<endl;
                break;
            case 3:
                shape="triangle";
                cout<<"enter three sides:";
                cin>>s1>>s2>>s3;
                cout<<"area:"<<area(s1,s2,s3)<<endl;
                break;
            case 4:
                shape="circle";
                cout<<"enter radius:";
                cin>>r;
                cout<<"area:"<<areas(r)<<endl;
                break;
            default:
                cout<<"invalid choice.\n";
        }
    }
};
// ==================== unit converter ====================
class unitconverter {
    double value;
    string unit;
public:
    unitconverter():value(0.0) {
        unit="meters";
    }
    double tometers() {
        if(unit=="kilometers")
            return value*1000.0;
        if(unit=="miles")
            return value*1600.0;
        return value;
    }
    double tokilometers() {
        if(unit=="meters")
            return value / 1000.0;
        if(unit=="miles")
            return value*1.6;
        return value;
    }
    double tomiles() {
        if(unit=="meters")
            return value / 1600.0;
        if(unit=="kilometers")
            return value / 1.6;
        return value;
    }
    void convert() {
        cout<<"\n=== unit converter ===\n";
        cout<<"enter value:";
        cin>>value;
        cout<<"enter unit(meters/kilometers/miles):";
        cin>>unit;
        cout<<value<<" "<<unit<<" is equal to:\n";
        cout<<tometers()<<" meters\n";
        cout<<tokilometers()<<" kilometers\n";
        cout<<tomiles()<<" miles\n";
    }
};
// ==================== fraction calculator ====================
class fraction {
    int n,d;
public:
    fraction(int n=0,int d=1):n(n),d(d) {}
    friend fraction add(fraction &f1,fraction &f2);
    friend fraction sub(fraction &f1,fraction &f2);
    friend fraction mul(fraction &f1,fraction &f2);
    friend fraction div(fraction &f1,fraction &f2);
    void display() {
        cout<<n<<"/"<<d<<endl;
    }
};
fraction add(fraction &f1,fraction &f2) {
    return fraction(f1.n*f2.d+f2.n*f1.d,f1.d*f2.d);
}
fraction sub(fraction &f1,fraction &f2) {
    return fraction(f1.n*f2.d-f2.n*f1.d,f1.d*f2.d);
}
fraction mul(fraction &f1,fraction &f2) {
    return fraction(f1.n*f2.n,f1.d*f2.d);
}
fraction div(fraction &f1,fraction &f2) {
    return fraction(f1.n*f2.d,f1.d*f2.n);
}
class fractioncalculator {
public:
    void calculate() {
        int n1,d1,n2,d2;
        char operation;
        cout<<"\n=== fraction calculator ===\n";
        cout<<"enter first fraction(n d):";
        cin>>n1>>d1;
        cout<<"enter second fraction(n d):";
        cin>>n2>>d2;
        cout<<"operations:+ -*/\nchoose:";
        cin>>operation;
        fraction f1(n1,d1),f2(n2,d2),result;
        switch(operation) {
            case '+':result=add(f1,f2); break;
            case '-':result=sub(f1,f2); break;
            case '*':result=mul(f1,f2); break;
            case '/':result=div(f1,f2); break;
            default:cout<<"invalid operation\n"; return;
        }
        cout<<"result:";
        result.display();
    }
};
// ==================== financial calculator ====================
class investment {
protected:
    double amount,rate;
    int years;
public:
    investment(double amt,double r,int y):amount(amt),rate(r),years(y) {}
    virtual ~investment()=default;
    virtual double calculatereturn() const=0;
    virtual double calculaterisk() const=0;
    virtual void display() const=0;
};
class stock:public investment {
    double volatility;
public:
    stock(double amt,double r,int y,double vol):investment(amt,r,y),volatility(vol) {}
    double calculatereturn() const override {
        return amount*pow(1+rate/100,years);
    }
    double calculaterisk() const override {
        return volatility*rate;
    }
    void display() const override {
        cout<<"stock investment:\n"
            <<"amount:$"<<amount<<"\nrate:"<<rate
            <<"%\nyears:"<<years<<"\nvolatility:"<<volatility<<"\n"
            <<"expected return:$"<<calculatereturn()
            <<"\nrisk factor:"<<calculaterisk()<<"\n\n";
    }
};
class bond:public investment {
    double creditrating;
public:
    bond(double amt,double r,int y,double rating):investment(amt,r,y),creditrating(rating) {}
    double calculatereturn() const override {
        return amount+(amount*rate/100*years);
    }
    double calculaterisk() const override {
        return 100-creditrating;
    }
    void display() const override {
        cout<<"bond investment:\n"
            <<"amount:$"<<amount<<"\nrate:"<<rate
            <<"%\nyears:"<<years<<"\ncredit rating:"<<creditrating<<"/100\n"
            <<"expected return:$"<<calculatereturn()
            <<"\nrisk factor:"<<calculaterisk()<<"\n\n";
    }
};
class financialcalculator {
    vector<shared_ptr<investment>> investments;
    vector<string> history;
public:
    void calculate() {
        char choice;
        do {
            cout<<"\n=== financial calculator ===\n"
                <<"1. add stock\n2. add bond\n"
                <<"3. display portfolio\n4. display history\n"
                <<"q. return to main menu\n"
                <<"choice:";
            cin>>choice;
            if(choice=='1'||choice=='2') {
                double amt,rate;
                int years;
                cout<<"amount:$"; cin>>amt;
                cout<<"rate(%):"; cin>>rate;
                cout<<"years:"; cin>>years;
                if(choice=='1') {
                    double volatility;
                    cout<<"volatility:"; cin>>volatility;
                    investments.push_back(make_shared<stock>(amt,rate,years,volatility));
                    history.push_back("added stock:$"+to_string(amt));
                } else {
                    double rating;
                    cout<<"credit rating(0-100):"; cin>>rating;
                    investments.push_back(make_shared<bond>(amt,rate,years,rating));
                    history.push_back("added bond:$"+to_string(amt));
                }
            } else if(choice=='3') {
                displayportfolio();
            } else if(choice=='4') {
                displayhistory();
            }
        } while(choice!='q'&&choice!='q');
    }
private:
    void displayportfolio() const {
        if(investments.empty()) {
            cout<<"portfolio is empty.\n";
            return;
        }
        for(const auto& inv:investments) {
            inv->display();
        }
        cout<<"total return:$"<<calculatetotalreturn()<<endl
            <<"total risk:"<<calculatetotalrisk()<<endl;
    }
    void displayhistory() const {
        cout<<"=== investment history ===\n";
        for(const auto& record:history) {
            cout<<record<<endl;
        }
    }
    double calculatetotalreturn() const {
        double total=0;
        for(const auto& inv:investments) {
            total += inv->calculatereturn();
        }
        return total;
    }
    double calculatetotalrisk() const {
        double total=0;
        for(const auto& inv:investments) {
            total += inv->calculaterisk();
        }
        return total;
    }
};
// ==================== scientific calculator ====================
class calculatorstate {
public:
    virtual ~calculatorstate()=default;
    virtual double add(double a,double b)=0;
    virtual double subtract(double a,double b)=0;
    virtual double multiply(double a,double b)=0;
    virtual double divide(double a,double b)=0;
};
class basicstate:public calculatorstate {
public:
    double add(double a,double b) override { return a+b; }
    double subtract(double a,double b) override { return a-b; }
    double multiply(double a,double b) override { return a*b; }
    double divide(double a,double b) override { return a / b; }
};
class scientificstate:public calculatorstate {
public:
    double add(double a,double b) override { return a+b; }
    double subtract(double a,double b) override { return a-b; }
    double multiply(double a,double b) override { return a*b; }
    double divide(double a,double b) override { return a / b; }
    static double sin(double a) { return::sin(a); }
    static double cos(double a) { return::cos(a); }
    static double tan(double a) { return::tan(a); }
    static double log(double a) { return::log(a); }
};
class programmingstate:public calculatorstate {
public:
    double add(double a,double b) override { return a+b; }
    double subtract(double a,double b) override { return a-b; }
    double multiply(double a,double b) override { return a*b; }
    double divide(double a,double b) override { return a / b; }
    static int bitwiseand(int a,int b) { return a & b; }
    static int bitwiseor(int a,int b) { return a | b; }
    static int bitwisexor(int a,int b) { return a ^ b; }
};
class scientificcalculator {
    calculatorstate* currentstate;
public:
    scientificcalculator():currentstate(new basicstate()) {}
    ~scientificcalculator() { delete currentstate; }
    void setstate(calculatorstate* newstate) {
        delete currentstate;
        currentstate=newstate;
    }
    void calculate() {
        cout<<"\n=== scientific calculator ===\n"
            <<"1. basic calculator\n"
            <<"2. scientific calculator\n"
            <<"3. programming calculator\n"
            <<"choose mode:";
        int choice;
        cin>>choice;
        switch(choice) {
            case 1:
                basiccalculation();
                break;
            case 2:
                setstate(new scientificstate());
                scientificcalculation();
                break;
            case 3:
                setstate(new programmingstate());
                programmingcalculation();
                break;
            default:
                cout<<"invalid choice\n";
        }
    }
private:
    void basiccalculation() {
        double a,b;
        char op;
        cout<<"enter first number:"; cin>>a;
        cout<<"enter operation(+,-,*,/):"; cin>>op;
        cout<<"enter second number:"; cin>>b;
        switch(op) {
            case '+':cout<<"result:"<<currentstate->add(a,b)<<endl; break;
            case '-':cout<<"result:"<<currentstate->subtract(a,b)<<endl; break;
            case '*':cout<<"result:"<<currentstate->multiply(a,b)<<endl; break;
            case '/':
                if(b!=0) cout<<"result:"<<currentstate->divide(a,b)<<endl;
                else cout<<"cannot divide by zero\n";
                break;
            default:cout<<"invalid operation\n";
        }
    }
    void scientificcalculation() {
        cout<<"1. basic operation\n2. scientific operation\nchoice:";
        int choice;
        cin>>choice;
        if(choice==1) {
            basiccalculation();
        } else if(choice==2) {
            string op;
            double num;
            cout<<"operation(sin/cos/tan/log):"; cin>>op;
            cout<<"number:"; cin>>num;
            if(op=="sin") cout<<"result:"<<scientificstate::sin(num)<<endl;
            else if(op=="cos") cout<<"result:"<<scientificstate::cos(num)<<endl;
            else if(op=="tan") cout<<"result:"<<scientificstate::tan(num)<<endl;
            else if(op=="log") cout<<"result:"<<scientificstate::log(num)<<endl;
            else cout<<"invalid scientific operation\n";
        }
    }
    void programmingcalculation() {
        int a,b;
        string op;
        cout<<"enter first integer:"; cin>>a;
        cout<<"operation(and/or/xor):"; cin>>op;
        cout<<"enter second integer:"; cin>>b;
        if(op=="and") cout<<"result:"<<programmingstate::bitwiseand(a,b)<<endl;
        else if(op=="or") cout<<"result:"<<programmingstate::bitwiseor(a,b)<<endl;
        else if(op=="xor") cout<<"result:"<<programmingstate::bitwisexor(a,b)<<endl;
        else cout<<"invalid programming operation\n";
    }
};
// ==================== calculator system ====================
class calculatorsystem {
public:
    void run() {
        shapecalculator shapecalc;
        unitconverter unitconverter;
        fractioncalculator fractioncalc;
        financialcalculator financialcalc;
        scientificcalculator scientificcalc;
        char choice;
        do {
            cout<<"\n=== calculator system ===\n"
                <<"1. shape calculator\n"
                <<"2. unit converter\n"
                <<"3. fraction calculator\n"
                <<"4. financial calculator\n"
                <<"5. scientific calculator\n"
                <<"q. quit\n"
                <<"enter your choice:";
            cin>>choice;
            switch(choice) {
                case '1':shapecalc.calculate(); break;
                case '2':unitconverter.convert(); break;
                case '3':fractioncalc.calculate(); break;
                case '4':financialcalc.calculate(); break;
                case '5':scientificcalc.calculate(); break;
                case 'q':case 'q':cout<<"exiting the calculator system.\n"; break;
                default:cout<<"invalid choice.\n";
            }
        } while(choice!='q'&&choice!='q');
    }
};
int main() {
    calculatorsystem system;
    system.run();
    return 0;
}