//
// Chicago Crime Analysis: top-5 crimes
//
// Woong Jin You
// U. of Illinois, Chicago
// CS341, Fall 2016
// HW #01
 
#include <iostream> 
#include <iomanip> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <vector> 
#include <algorithm>
 
using namespace std;
 
using std::string;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::getline;
using std::stoi;
using std::sort;
using std::cout;
using std::endl;
 
class crime_code {
public:
    int IUCR;
    string Primary_description, Secondary_description;
 
    crime_code(int iucr, string primary_description, string secondary_description)
        : IUCR(iucr), Primary_description(primary_description), Secondary_description(secondary_description)
    {}
};
 
class crime {
public:
    int Mon, D, Y, H, Min; //time vars
    int IUCR, Beat, District, Ward, Community;
    bool Arrest, Domestic;
    string Primary_description, Secondary_description;
 
    crime(int mon, int d, int y, int h, int min,
        int iucr, bool arrest, bool domestic, int beat,
        int district, int ward, int community)
        : Mon(mon), D(d), Y(y), H(h), Min(min),
        IUCR(iucr), Arrest(arrest), Domestic(domestic), Beat(beat),
        District(district), Ward(ward), Community(community)
    { }
};
 
void input_crime_codes(string fileName, vector<crime_code> & crime_codes) {
    ifstream file(fileName);
    int IUCR;
    string IUCR_string, primary_desc, sec_desc, line;
 
    if (!file.good()) {
        cout << "connot open file!" << endl;
        return;
    }
    
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
 
        //  parse line
        getline(ss, IUCR_string, ',');
        getline(ss, primary_desc, ',');
        getline(ss, sec_desc, ',');
 
        IUCR = stoi(IUCR_string);
 
        crime_code C(IUCR, primary_desc, sec_desc);
 
        // insert @ end:
        crime_codes.push_back(C);
    }
}
 
void input_crimes(string fileName, vector<crime> & crimes) {
    ifstream file(fileName);
    bool Arrest, Domestic;
    string D, Mon, Y, H, Min;
    string IUCR, Beat, District, Ward, Community;
    string Arrest_s, Domestic_s;
    string line;
 
    if (!file.good()) {
        cout << "connot open file!" << endl;
        return;
    }
 
    getline(file, line); // skip header
    while (getline(file, line)) {

        stringstream ss(line);
 
        //  parse line
        getline(ss, Mon, '/');
        getline(ss, D, '/');
        getline(ss, Y, ' ');
        getline(ss, H, ':');
        getline(ss, Min, ',');
        getline(ss, IUCR, ',');
        getline(ss, Arrest_s, ',');
        getline(ss, Domestic_s, ',');
        getline(ss, Beat, ',');
        getline(ss, District, ',');
        getline(ss, Ward, ',');
        getline(ss, Community, ',');
 
        (Arrest_s == "TRUE") ? (Arrest = true) : (Arrest = false);
        (Domestic_s == "TRUE") ? (Domestic = true) : (Domestic = false);
 
        crime C(stoi(Mon), stoi(D), stoi(Y), stoi(H), stoi(Min), stoi(IUCR), Arrest,
            Domestic, stoi(Beat), stoi(District), stoi(Ward), stoi(Community));
 
        // insert @ end:
        crimes.push_back(C);
    }
 
}
 
void output(vector<crime_code> crime_codes, vector<crime> crimes) {
    cout << "** Crime Analysis **" << endl << endl;
 
    // Sort vector by date in descending order
    sort(crimes.begin(),
        crimes.end(),
 
        [](crime c1, crime c2)
    {
        if (c1.Y < c2.Y)
            return true;
        else if (c1.Y > c2.Y)
            return false;
        else {
            if (c1.Mon < c1.Mon)
                return true;
            else if (c1.Mon > c1.Mon)
                return false;
            else {
                if (c1.D < c1.D)
                    return true;
                else
                    return false;
            }
        }
    }); 
 
    // display date range 
    int i_end = crimes.size() - 1;
    cout << "Date range: ";
    cout << crimes[i_end].Mon << "/" << crimes[i_end].D << "/" << crimes[i_end].Y <<" "<< crimes[i_end].H << ":" << crimes[i_end].Min << " - ";
    cout << crimes[0].Mon << "/" << crimes[0].D << "/" << crimes[0].Y << " " << crimes[0].H << ":" << crimes[0].Min << endl;
 
    // Sort vector by crime code in descending order
    sort(crime_codes.begin(),
        crime_codes.end(),
 
        [](crime_code c1, crime_code c2)
    {
        return c1.IUCR < c2.IUCR;
    });
 
    // display crime codes
    cout << "# of crime codes: " << crime_codes.size() << endl;
    for (int i = 0; i < 3; i++) {
        cout << crime_codes[i].IUCR << "    " << crime_codes[i].Primary_description << ":" << crime_codes[i].Secondary_description << endl;
    }
    cout << "..." << endl;
    for (int i = (crime_codes.size() - 3); i < crime_codes.size(); i++) {
        cout << crime_codes[i].IUCR << "    " << crime_codes[i].Primary_description << ":" << crime_codes[i].Secondary_description << endl;
    }
 
    // display crimes
    cout << endl << "# of crime: " << crimes.size() << endl;
    for (int i = 0; i < 3; i++) {
        cout << crimes[i].IUCR << ":    " << crimes[i].Mon << "/" << crimes[i].D << "/" << crimes[i].Y << " " << crimes[i].H << ":" << crimes[i].Min;
        cout << ", " << crimes[i].Beat << ", " << crimes[i].District << crimes[i].Community << endl;
    }
    cout << "..." << endl;
    for (int i = (crimes.size() - 3); i < crimes.size(); i++) {
        cout << crimes[i].IUCR << ":    " << crimes[i].Mon << "/" << crimes[i].D << "/" << crimes[i].Y << " " << crimes[i].H << ":" << crimes[i].Min;
        cout << ", " << crimes[i].Beat << ", " << crimes[i].District << crimes[i].Community << endl;
    }
 
    // Sort vector by crime code frequency in descending order
    //sort(crimes.begin(),
    //  crimes.end(),
 
    //  [](crime c1, crime c2)
    //{
    //  int count1=0, count2=0;
    //  for (int i = 0; i < crimes.size(); i++) {
    //      if (crimes[i].IUCR = c1.IUCR) { count1++; };
    //      if (crimes[i].IUCR = c2.IUCR) { count2++; };
    //  }
    //  return count1 < count2;
    //});
 
    // display top-5 crimes
    cout << endl << "** Top-5 Crimes **" << endl;
    cout << endl << "Code:  Total, Description" << endl;
 
    // done
    cout << "** Done **" << endl;
}
 
int main() {
 
    vector<crime_code> crime_codes;
    vector<crime> crimes;

    input_crime_codes("crime-codes.csv", crime_codes);
    input_crimes("crimes.csv", crimes);
    //input_crimes("crimes-2.csv", crimes);
 
    //output(crime_codes, crimes);

    return 0;
 
}