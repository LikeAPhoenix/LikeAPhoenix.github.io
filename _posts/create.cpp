#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <ctime>
using namespace std;

/*
void out_day(tm *stime) {
  printf("%04d-%02d-%02d", 1900 + stime->tm_year, 1 + stime->tm_mon, stime->tm_mday);
}
void out_time(tm *stime) {
  printf("%02d:%02d:%02d", stime->tm_hour, stime->tm_min, stime->tm_sec);
}

void out_day(ofstream *out, tm *stime) {
  *out << 1900 + stime->tm_year
      << "-" << setw(2) << setfill('0') << 1 + stime->tm_mon
      << "-" << setw(2) << setfill('0') << stime->tm_mday;
}
void out_time(ofstream *out, tm *stime) {
  cout << setw(2) << setfill('0') << stime->tm_hour;
  *out << setw(2) << setfill('0') << stime->tm_hour
      << ":" << setw(2) << setfill('0') << stime->tm_min
      << ":" << setw(2) << setfill('0') << stime->tm_sec;
}
*/

string get_date(tm *stime) {
  string date = to_string(1900 + stime->tm_year) + "-";  // date
  if (1 + stime->tm_mon < 10) {
    date.append("0");
  }
  date += to_string(1 + stime->tm_mon) +"-";
  if (stime->tm_mday < 10) {
    date.append("0");
  }
  date += to_string(stime->tm_mday);
  return date;
}

string get_time(tm *stime) {
  string time;
  if (stime->tm_hour < 10) {
    time.append("0");
  } 
  time += to_string(stime->tm_hour) + ":";
  if (stime->tm_min < 10) {
    time.append("0");
  }
  time += to_string(stime->tm_min) + ":";
  if (stime->tm_sec < 10) {
    time.append("0");
  }
  time += to_string(stime->tm_sec);
  return time;
}

void write_in_md(ofstream *out, string date, string time) {
/*
  string title;
  string subtitle;
  string tags;

  cin.sync();
  cout << "Please input title:";
  getline(cin, title);
  cout << "Please input subtitle:";
  getline(cin, subtitle);
  cout << "Please input tags:";
  getline(cin, tags);
*/

  *out << "---" << endl;
  *out << "layout:     post" << endl;
  *out << "title:      \"" << "\"" << endl;
  *out << "subtitle:   \"" << "\"" << endl;
  *out << "date:       " << date << " " << time << endl;
  *out << "author:     \"XDong\"" << endl;
  *out << "header-img: \"img/post-bg-wlop-2880x1800.jpg\"" << endl;
  *out << "tags:" << endl << "    - " << endl;
  *out << "---" << endl;
}



int main() {
  time_t t = time(NULL);
  tm *stime = localtime(&t);

  string date = get_date(stime); 
  string time = get_time(stime); 
  string folder_name;
  cout << "Please input foldername:";
  getline(cin, folder_name);
  string file_name;
  cout << "Please input file name:";
  cin >> file_name;
  ifstream in(folder_name + "/" + date + "-" + file_name + ".md", ios::in);  // file is exist or not
  if (!in) {  // create new file
    ofstream *out = new ofstream;
    out->open(folder_name + "/" + date + "-" + file_name + ".md", ios::out);
    write_in_md(out, date, time);  // write something in mardown file
    cout << "Perfect!" << endl;
  } else {
    cout << "File is exist!!!" << endl;
  }
  return 0;
}