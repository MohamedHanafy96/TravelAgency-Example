#include <iostream>
#include <iomanip>
using namespace std;

typedef unsigned short int usi;
typedef const unsigned short int cusi;
const int N = 1e2+5;
class Date
{
private :
    usi days, month,year;
    cusi DaysInMonth [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;

public:
    usi get_days() const
    {
        return days;
    }
    usi get_month() const
    {
        return month;
    }
    usi get_year() const
    {
        return year;
    }
    Date( usi a = 0, usi b = 0,  usi c = 0)
    {

        days = a;
        month = b;
        year = c ;
    }

    Date operator+(int nDays) const
    {
        Date tmp = *this;
        int maxnDays = DaysInMonth[tmp.month];
        int newday = tmp.days+nDays;
        int newmonth = tmp.month+(newday/maxnDays);
        tmp.days = (((newday % maxnDays) == 0 ? newday : (newday % maxnDays)));
        tmp.month = (((newmonth % 12) == 0 ? newmonth : (newmonth % 12)));
        tmp.year = (tmp.year+(newmonth/12));
        return tmp;
    }
    Date& operator = (const Date& tmp)
    {
        days = tmp.days;
        month = tmp.month;
        year = tmp.year;
        return *this;
    }
    friend ostream& operator<<(ostream& out, Date& tmp) ;
    friend istream& operator>>(istream& in, Date& tmp);

};
ostream& operator<<(ostream& out, Date& tmp)
{
    if (tmp.days <= 9)
        out <<0;
    out << tmp.days << "." ;
    if (tmp.month <= 9)
        out <<0;
    out << tmp.month << ".";
    out << tmp.year;
    return out;
}

istream& operator>>(istream& in, Date& tmp)
{
    char dot;
    in >> tmp.days >> dot >> tmp.month >> dot >> tmp.year;
    return in;
}




class Board
{
    enum  Type {noMeal = 0, breakfast = 1, halfPension = 2, AllInclusive = 3  };
    Type type;
public:
    Board (char c)
    {
        switch(c)
        {
        case 'a':
            type = AllInclusive;
        case 'b':
            type = breakfast;
        case 'h':
            type = halfPension;
        case 'n':
            type = noMeal;
        default:
            type= noMeal;
        }
    }
    friend ostream& operator << (ostream & out, Board& tmp) ;

};

ostream& operator << (ostream & out, Board& tmp)
{
    switch (tmp.type)
    {
    case (Board :: noMeal):
        out << "noMeal";
        break;
    case (Board :: breakfast):
        out << "breakfast";
        break;
    case  (Board :: halfPension):
        out << "halfPension";
        break;
    case (Board :: AllInclusive):
        out << "AllInclusive";
        break;
    default:
        out << "Not an option";
    }

    return out;
}
class Hotel
{
public:
    Hotel(string n,int ni,int s, int d, double ps, double pd, bool p, Board* b )
    {
        name = n ;
        nights = ni;
        singles = s;
        doubles = d ;
        priceNightSingle = ps ;
        priceNightDouble = pd ;
        parking = p;
        board = b;
    }
    virtual ~Hotel()
    {

    }

    string Getname()
    {
        return name;
    }
    void Setname(string val)
    {
        name = val;
    }
    Date Getarrival()
    {
        return arrival;
    }
    void Setarrival(Date val)
    {
        arrival = val;
    }
    int Getnights()
    {
        return nights;
    }
    void Setnights(int val)
    {
        nights = val;
    }
    int Getsingles()
    {
        return singles;
    }
    void Setsingles(int val)
    {
        singles = val;
    }
    int Getdoubles()
    {
        return doubles;
    }
    void Setdoubles(int val)
    {
        doubles = val;
    }
    Board* Getboard()
    {
        return board;
    }
    void Setboard(Board* val)
    {
        board = val;
    }
    double getprice()
    {
        double tp = nights*(priceNightDouble*singles + doubles*priceNightSingle);
        return parking? nights*10 + tp: tp;
    }
    double GetpriceNightSingle()
    {
        return priceNightSingle;
    }
    void SetpriceNightSingle(double val)
    {
        priceNightSingle = val;
    }
    double GetpriceNightDouble()
    {
        return priceNightDouble;
    }
    void SetpriceNightDouble(double val)
    {
        priceNightDouble = val;
    }
    Date getCheckout()
    {
        return (arrival+nights);
    }


private:
    string name;
    Date arrival;
    int nights;
    int singles;
    int doubles;
    Board* board;
    double priceNightSingle;
    double priceNightDouble;
    bool parking;
};

class Transportation
{
public :
    virtual ~Transportation()
    {
        cout << "This is transpotation, yoo" ;
    };
    virtual bool withTransfer() = 0 ;
    virtual double getPrice() = 0 ;
    virtual void  print() = 0 ;
};

class SelfOrganised :public Transportation
{
public :
    SelfOrganised()
    {
    }
    virtual ~SelfOrganised()
    {

    }
    double getPrice()
    {
        return 0.00;
    }
    bool withTransfer()
    {
        return false ;
    }
    void  print()
    {
        cout << "self organised transport\n";
    }
} ;

class PublicTransport : public Transportation
{
protected :
    Date departure;
    string code, from, to ;
    double priceOneSeat;
    bool firstClass;
public:

    PublicTransport(Date dep, string cod, string frm, string t, double pos, bool fc = 0)
    {
        //@TODO reverse the right and left sides
        departure = dep  ;
        code = cod  ;
        from = frm ;
        to = t ;
        priceOneSeat = pos ;
        firstClass = fc  ;
    }
    virtual ~PublicTransport()
    {
        cout << "Public transport deleted";
    };


};

class Train  : public PublicTransport
{
public:
    Train(Date d, string co, string fr, string t, double p, bool fc = 0 ) : PublicTransport(d,co,fr,t,p,fc)
    {

    }
    double getPrice()
    {
        return priceOneSeat;
    }
    virtual ~Train()
    {
        cout << "Train is deleted successfully\n";
    }
    bool withTransfer()
    {
        return 0;
    }
    void print()
    {
        cout << "main train station of departure: " << from << endl << "main train station of arrival: " << to <<endl << "price for one passenger: " <<fixed << setprecision(5) << priceOneSeat <<endl;
    }

};

class Flight : public PublicTransport
{
private :

    bool transfer ;

public :
    Flight(Date d, string co, string fr, string t, double p, bool fc = 0, bool tr  = 1 ) : PublicTransport(d,co,fr,t,p,fc)
    {
        transfer = tr;
    }
    virtual ~ Flight()
    {
        cout << "flight is deleted\n" ;
    }
    bool withTransfer()
    {
        return transfer ;
    }
    double getPrice()
    {
        return ((firstClass)? priceOneSeat*2 : priceOneSeat);
    }
    void print ()
    {
        cout << "Airport of departure: " << from << endl << "Airport of arrival: " << to <<endl << "price for one passenger: " <<fixed << setprecision(5) << ((firstClass)? priceOneSeat*2 : priceOneSeat) <<endl;

    }
};
class Trip
{
public:
    Trip(int n,Hotel* h, Transportation* b, Transportation* o  )
    {
        travellers = n;
        hotel = h;
        transportBack = b;
        transportout = o;
        //no = ++lastNo;
    }
    virtual ~Trip();

    const unsigned int Getno()
    {
        return no;
    }
    /*void Setno(const unsigned int val)
    {
        no = val;
    }*/
    const unsigned int GetlastNo()
    {
        return lastNo;
    }
    void SetlastNo(const unsigned int val)
    {
        lastNo = val;
    }
    unsigned int Gettravellers()
    {
        return travellers;
    }
    void Settravellers(unsigned int val)
    {
        travellers = val;
    }
    Hotel Gethotel()
    {
        return *hotel;
    }
    void Sethotel(Hotel val)
    {
        *hotel = val;
    }

    double get_price ()
    {
        cout << "Total price of the journey : \n";
        return (hotel->getprice()+transportBack->getPrice()+transportout->getPrice());
    }
    void print ()
    {
        Date tmp = hotel->Getarrival();
        bool transfer = transportBack->withTransfer();
        Board* ty = hotel->Getboard();
        cout << "trip inquiry" << no<<  "for " << (2*(hotel->Getdoubles()) +hotel->Getsingles()) << "person(s)\n";
        cout << "check in :    hotel" << tmp<< "  " << hotel->Getname() << "  for" << hotel->Getnights() << " Nights   \n" << hotel->Getsingles() << " Single room(s)  \n" << hotel->Getdoubles() << " double room(s)\n";
        cout << ty << endl;
        cout << "outward journey : " ;
        transportout->print();
        cout << "backward journey : " ;
        transportBack->print() ;
        cout << transfer << endl << "   " << get_price();
    }

private:
    const unsigned int no = ++lastNo;
    static unsigned int lastNo;
    unsigned int travellers;
    Hotel *hotel;
    Transportation* transportout ;
    Transportation* transportBack;
};

unsigned int Trip:: lastNo = 0;
class TravelAgency
{
private :
    Trip* trips[N] {} ;
    int ct;
public :
    TravelAgency()
    {
        ct = 0;
    }
    void add(Trip* t)
    {
        trips[ct] = t;
        ct++;
    }
    void remove(Trip* t)
    {
        int idx = -1 ;
        for (int i = 0 ; i<ct ; ++i)
        {
            if (trips[i]->Getno() == t->Getno())
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
            return;
        delete trips[idx];
        for (int i = idx ; i<ct ; ++i)
        {
            trips[i] = trips[i+1];
        }
        ct--;
    }
    Trip* search(unsigned int n)
    {
        for (int i = 0 ; i<ct ; ++i)
        {
            if (trips[i]->Getno() == n)
                return trips[i];
        }
        return 0;
    }
    void print()
    {
        for (int i = 0 ; i<ct ; ++i)
        {
            cout << "Trip number " << i+1 << ": \n";
            trips[i]->print();
            cout << "\n\n";
        }
    }
};

Hotel* ReadHotel()
{
    string name;
    Date date;
    int singles;
    int doubles;
    double ps;
    double pd;
    int nights;
    bool parking = 0;
    char ty,park;
    cout << "name of hotel: ";
    cin >> name ;
    cout << "\narrival on: ";
    cin >>date;
    cout << "\nhow many nights:";
    cin >> nights;
    cout << "\nhow many single bed rooms: ";
    cin >> singles;
    cout << "how many double bed rooms: ";
    cin >> doubles;
    cout << "\na all inclusive\n" << "b breakfast\n" << "h half board\n" << "w without meals\n" ;
    cin >> ty;
    cout << "price one night in single bed room: " ;
    cin >> ps;
    cout << "\nPrice one night in double bed room: " ;
    cin >> pd ;
    cout << "with parking (y(es) or n(o)): " ;
    cin >> park ;
    if (park =='y')
        parking = 1;
    Board* type = new Board(ty);
    Hotel* ret = new Hotel(name,nights,singles,doubles,ps,pd,parking,type);
    return (ret);
}
Train* ReadTrain()
{
    Date dt;
    string cod;
    string frm;
    string to;
    double price;
    bool fc = 0;
   cout<< " code of Train: ";
   cin >> cod;
   cout << "\nstation of departure: ";
   cin >>frm;
   cout << "\nstation of arrival: ";
   cin >> to;
   cout << "\nprice for one passenger: ";
   cin >> price ;
   cout << "\nFirst class??";
   cin >> fc;
   if (fc == 1){cout << "The seat is first class\n";} else {cout << "Not first class\n";}

    Train* t = new Train(dt,cod,frm,to,price,fc);
    return t ;
}
Flight* ReadFlight()
{
    Date dt;
    string cod;
    string frm;
    string to;
    double price;
    bool fc = 0;
    bool transfer = 1;
   cout<< " code of flight: ";
   cin >> cod;
   cout << "\nairport of departure: ";
   cin >>frm;
   cout << "\nairport of arrival: ";
   cin >> to;
   cout << "\nprice for one passenger: ";
   cin >> price ;
   cout << "\nFirst class??";
   cin >> fc;
   if (fc == 1){cout << "The seat is first class\n";} else {cout << "Not first class\n";}
   cout << "\n with or without transfer";
   cin >> transfer;
   if (transfer == 0){cout << "there is no transfer\n";} else {cout << "With transfer";}
    Flight* f = new Flight(dt,cod,frm,to,price,fc,transfer);
    return f;
}
int main()
{
    int mainchoice ;
    TravelAgency* TA = new TravelAgency();
    while(true)
    {
        cout << "HOTLINE TRAVEL AGENCY\n\n0 end\n1 new trip\n2 search trip\n3 show all trip offers\n";
        cin >> mainchoice;
        switch (mainchoice)
        {
        case (0) :
        {
            return 0 ;
            break;
        }
        case (1) :
        {
            Hotel* hotel = ReadHotel();
            int choice = 0;
            Transportation* backward;
            Transportation* outward;
            cout << "please choose transport for outward journey \n0 self organised \n 1 by flight\n 2 by train\n";
            cin >> choice;
            switch (choice)
            {
            case (0) :
                outward = new SelfOrganised();
                break;
            case (1) :
                outward = ReadFlight();
                break;
            case (2) :
                outward= ReadTrain();
                break;
            default:
                return 0;
            }
            cout << "please choose transport for journey back \n0 self organised \n 1 by flight\n 2 by train\n";
            cin >> choice;
            switch (choice)
            {
            case (0) :
                backward = new SelfOrganised();
                break;
            case (1) :
                backward = ReadFlight();
                break;
            case (2) :
                backward = ReadTrain();
                break;
            default:
                return 0;
            }
            Trip* newtrip = new Trip(hotel->Getsingles()+2*hotel->Getdoubles(),hotel,backward,outward);
            TA->add(newtrip);
            break;
        }
        case (2) :
        {
            int tripnumber;
            cin >> tripnumber;
            Trip* search_trip = TA->search(tripnumber);
            if (search_trip==0)
                cout << "trip not found\n";
            else
            {
                char c;
                search_trip->print();
                cout <<"\n";
                cout << "(d)elete or (n)ot";
                cin >> c;
                if (c == 'd')
                    TA->remove(search_trip);
            }
            break;
        }
        case (3) :
            TA->print();
            break;
        default:
            return 0;

        }
    }
    return 0;
}
