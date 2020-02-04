#ifndef TRIP_H
#define TRIP_H


class Trip
{
    public:
        Trip();
        virtual ~Trip();

        const unsigned int Getno() { return no; }
        void Setno(const unsigned int val) { no = val; }
        const unsigned int GetlastNo() { return lastNo; }
        void SetlastNo(const unsigned int val) { lastNo = val; }
        unsigned int Gettravellers() { return travellers; }
        void Settravellers(unsigned int val) { travellers = val; }
        Hotel Get*hotel() { return *hotel; }
        void Set*hotel(Hotel val) { *hotel = val; }
        int Get*transportOutward() { return *transportOutward; }
        void Set*transportOutward(int val) { *transportOutward = val; }
        int Get*transportBack() { return *transportBack; }
        void Set*transportBack(int val) { *transportBack = val; }
        int Get*next() { return *next; }
        void Set*next(int val) { *next = val; }

    protected:

    private:
        const unsigned int no;
        const unsigned int lastNo;
        unsigned int travellers;
        Hotel *hotel;
        int *transportOutward;
        int *transportBack;
        int *next;
};

#endif // TRIP_H
