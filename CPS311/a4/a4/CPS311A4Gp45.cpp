//CPS311 F2015 A4 Gp45 Plotnik, D; Fernandes, S; Burger, C
#include <iostream>
#include <string.h>
using namespace std;
class shopper {
    protected: 
        char* shopper_name; 
        int years_a_member;
        double avg_monthly_purchases;
        double membership_cost;
        double nominal_membership_cost = 50;
    public:
        shopper(int yrs_a_mbr, char* sh_nm, double av_mnth_prchs = 250);
        ~shopper() {
            cout << "In the destructor" << endl;
            delete[] shopper_name;
        }
        virtual void set_membership_cost() {
            if (years_a_member < 5) {
                membership_cost = nominal_membership_cost*(1 - 0.04*years_a_member) - 0.5*0.01*avg_monthly_purchases;
            }
            else {
                membership_cost = 30;
            }
        }
        double get_membership_cost() {
            return membership_cost + 2;
        }
        char* get_shopper_name() {
            return shopper_name;
        }
};

shopper::shopper(int yrs_a_mbr, char* sh_nm, double av_mnth_prchs) : years_a_member( yrs_a_mbr ) {
    shopper_name = new char[strlen(sh_nm)+1];
    strcpy(shopper_name, sh_nm);
    avg_monthly_purchases = av_mnth_prchs;
}

ostream& operator<<(ostream& out, shopper shpr)
{
    out << shpr.get_shopper_name()
        << " has a yearly membership cost of $"
        << shpr.get_membership_cost()
        << endl;
    return out;
}


class family_shopper : public shopper {
    private: 
        double family_discount;
    public:
        family_shopper(char* f_sh_nm, double fam_disc = 10, int yrs_a_mbr = 2, double av_mnths_prchs = 100.00) : shopper(yrs_a_mbr, f_sh_nm, av_mnths_prchs) {
            family_discount = fam_disc;
        }
        virtual void set_membership_cost() {
            if (years_a_member < 5) {
                membership_cost = nominal_membership_cost*(1 - 0.04*years_a_member) - 0.5*0.01*avg_monthly_purchases;
            }
            else {
                membership_cost = 30;
            }
            membership_cost *= (1 - ((double)(family_discount)) / 100);
        }
        friend ostream& operator<<(ostream& out, family_shopper f_shpr) {
            cout.setf(ios::fixed);
            cout.precision(2);
            out << f_shpr.shopper_name
                << " is a family shopper whose annual membership with discount of "
                << f_shpr.family_discount
                << "% is $"
                << f_shpr.membership_cost
                << endl;

            return out;
        }
};

int main() {
    cout << "CPS311 F2015 A4 Gp45 Plotnik, D; Fernandes, S; Burger, C" << endl;
    static shopper shpr1(3, "ABC", 600);
    static shopper shpr2(6, "DEF");
    static family_shopper f_shpr("GHI", 12);

    shopper *ptr;

    ptr = &shpr1;
    ptr->set_membership_cost();
    cout << shpr1;

    ptr = &shpr2;
    ptr->set_membership_cost();
    cout << shpr2;

    ptr = &f_shpr;
    ptr->set_membership_cost();
    cout << f_shpr;
    return 0;
}