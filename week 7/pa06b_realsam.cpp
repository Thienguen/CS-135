/// @file pa06b.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/9/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This program reads and filters a delimited data
/// stream to identify and report those transactions occurring
/// on a given weekday. The largest quantity and sale are noted
/// and reported at the end of the report, along with a count of
/// items sold and the total sales for the period.
///
/// @note Field numbers:
/// 1     The sale date in YYYY-MM-DD order, delimited with '-'
/// 2     The sale time in HH:MM:SS order, delimited with ':'
/// 3     The stock number ([10000-99999])
/// 4     The sale price (dollars)
/// 5     The number of units sold
/// 6     The department (may have spaces)
///
/// @note People who helped me: NONE
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include i/o libs
#include <iostream>
#include <string>
#include <iomanip>

namespace cs135 {

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
void read_target(int& target);

void read_3_ints(int& n1, int& n2, int& n3);

void read_date(int& year, int& month, int& day);

void read_time(int& hour, int& minute, int& sec);

void read_transaction(int& stock, std::string& dept, double& price, int& qty);

void read_record(int& hour, int& minute, int& second,
                 std::string& department, double& price,
                 int& quantity, int& stock);

void update_accumulators(double price, int& largest_qty, int& total_qty,
                         int qty, double& sales, double& largest_sales,
                         double& total_sales);

void write_header(const std::string& weekday_name = "");

void write_detail(double jdate, int stock, const std::string& dept,
                 double price, int qty, double total);

void write_summary(int largest_qty, int total_qty, double largest_sales,
                   double total_sales);

void process_record(int year, int month, int day,
                    int& largest_qty, int& total_qty,
                    double& largest_sales, double& total_sales);

int larger(int a, int b);

double larger(double a, double b);

std::string weekday_name(int weekday);

long julian_day_number(int year, int month, int day);

double julian_date(int year, int month, int day,
                   int hour, int minute, int sec);

int weekday(int year, int month, int day);

}  // end namespace cs135

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
// variable declarations(s)
int target;
int year;
int month;
int day;

#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif

cs135::read_target(target);

// need to read the date to start the while loop to establish sentinal
cs135::read_date(year, month, day);

if (std::cin.good()) {
    // initialize accumulators
    double sales_max   = 0.0;
    double sales_total = 0.0;
    int    qty_max     = 0;
    int    qty_total   = 0;

    cs135::write_header(cs135::weekday_name(target));
    std::cout << std::fixed << std::showpoint;

    do {
        if (cs135::weekday(year, month, day) == target) {
            cs135::process_record(year, month, day,
                            qty_max, qty_total, sales_max, sales_total);
        } else {
            std::cin.ignore(255, '\n');
        }

        cs135::read_date(year, month, day);  // Loop update
    } while (std::cin.good());

    cs135::write_summary(qty_max, qty_total, sales_max, sales_total);
}

// return to the operating system
return EXIT_SUCCESS;
}

namespace cs135 {
/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Read the target day from stdin
/// @note target day is on its own line.
/// @param [out] target is user entered ISO week day
void read_target(int& target) {
std::cin >> target;
}

/// Read three ints from stdin, parse and return via ref params.
/// @note input format int(a char)int(a char)int
/// @param [out] n1 is user entered first integer
/// @param [out] n2 is user entered second integer
/// @param [out] n3 is user entered third integer
void read_3_ints(int& n1, int& n2, int& n3) {
std::cin >> n1;      // get the first integer
std::cin.ignore();   // ignore the delimiter
std::cin >> n2;      // get the second integer
std::cin.ignore();   // ignore the second delimiter
std::cin >> n3;      // get the third integer
}

/// Read a date from stdin, parse and return via ref params.
/// @note input format YYYY-MM-DD
/// @param [out] year is user entered year
/// @param [out] month is user entered month
/// @param [out] day is user entered day
void read_date(int& year, int& month, int& day) {
read_3_ints(year, month, day);
}

/// Read a time from stdin, parse and return via ref params.
/// @note input format HH:MM:SS
/// @param [out] hour is user entered hour
/// @param [out] minute is user entered minute
/// @param [out] sec is user entered day
void read_time(int& hour, int& minute, int& sec) {
read_3_ints(hour, minute, sec);
}

/// Read transaction details from stdin and return via ref params.
/// @param [out] stock The stock.
/// @param [out] price The price.
/// @param [out] qty The quantity.
/// @param [out] dept The department.
void read_transaction(int& stock, std::string& dept, double& price, int& qty) {
std::cin >> stock;
std::cin.ignore();
std::cin >> price;
std::cin.ignore();
std::cin >> qty;
std::cin.ignore();
getline(std::cin, dept);
}

/// Read an entire record
/// @param [out] hour The hour.
/// @param [out] minute The minute.
/// @param [out] second The second.
/// @param [out] department The department.
/// @param [out] price The price.
/// @param [out] quantity The quantity.
/// @param [out] stock The stock.
void read_record(int& hour, int& minute, int& second,
                std::string& department, double& price,
            int& quantity, int& stock) {
std::cin.ignore();                                       // ignore delimiter
read_time(hour, minute, second);
std::cin.ignore();                                       // ignore delimiter
read_transaction(stock, department, price, quantity);
}

/// Update accumulators
/// @param          price price
/// @param [in,out] largest_qty largest quantity
/// @param [in,out] total_qty total quantity
/// @param          qty quantity
/// @param [out]    sales The sales
/// @param [in,out] largest_sales largest sales
/// @param [in,out] total_sales total sales
void update_accumulators(double price, int& largest_qty, int& total_qty,
                    int qty, double& sales, double& largest_sales,
                    double& total_sales) {
sales = price * qty;
largest_qty = larger(qty, largest_qty);
largest_sales = larger(sales, largest_sales);
total_qty += qty;
total_sales += sales;
}

/// Write report title and header.
/// @param weekday_name (optional) The name of the day.
void write_header(const std::string& weekday_name) {
std::cout << "Sales Report";

//  handle default day name
if (weekday_name != "") {
    std::cout << " - " << weekday_name << "s" << std::endl;
}
std::cout << std::endl;
std::cout << "Julian Date     Stock  Department                    "
"Price  Qty    Total\n";
std::cout << std::string(72, '-') << std::endl;
}

/// Output detail line
/// @param jdate The jdate.
/// @param stock The stock.
/// @param dept The department.
/// @param price The price.
/// @param qty The qty.
/// @param total Number of.
void write_detail(double jdate, int stock, const std::string& dept,
                double price, int qty, double total) {
std::cout << std::left
<< std::setprecision(6)
<< std::setw(16) << jdate
<< std::setprecision(2)
<< std::setw(7) << stock
<< std::setw(28) << dept
<< std::right
<< '$' << std::setw(6) << price
<< std::setw(4) << qty
<< std::setw(3) << '$' << std::setw(7) << total << '\n';
}

/// Output the summary
/// @param largest_qty The largest qty
/// @param total_qty The total qty
/// @param largest_sales The largest sales
/// @param total_sales The total sales
void write_summary(int largest_qty, int total_qty, double largest_sales,
                double total_sales) {
std::cout << std::setprecision(2) << '\n';
std::cout << "Largest quantity: " << largest_qty << '\n';
std::cout << "Largest sale:     " << '$' << largest_sales << "\n\n";
std::cout << "Total items sold: " << total_qty << '\n';
std::cout << "Total sales:      " << '$' << total_sales << '\n';
}

/// Returns the larger of a or b (overloads).
/// @param a first number for comparison
/// @param b second number for comparison
int larger(int a, int b) {
return (a > b)? a : b;
}
// add double type overload
double larger(double a, double b) {
return (a > b)? a : b;
}

/// Process the record
/// @param year year
/// @param month month
/// @param day day
/// @param [in,out] largest_qty largest quantity
/// @param [in,out] total_qty total quantity
/// @param [in,out] largest_sales largest sales
/// @param [in,out] total_sales total sales
void process_record(int year, int month, int day,
                int& largest_qty, int& total_qty,
                double& largest_sales, double& total_sales) {
std::string department;
int    hour;
int    minute;
double price;
int    quantity;
double sales;
int    second;
int    stock;

read_record(hour, minute, second, department, price, quantity, stock);
update_accumulators(price, largest_qty, total_qty,
                    quantity, sales, largest_sales, total_sales);
write_detail(julian_date(year, month, day, hour, minute, second),
                stock, department, price, quantity, sales);
}

/// -----------------------------------------------------------------------
/// Functions from previous assignments
/// -----------------------------------------------------------------------

/// Integer weekday to name
/// @param weekday is the ISO weekday number.
/// @returns the weekday string, else error.
std::string weekday_name(int weekday) {
std::string name;

switch (weekday) {
    case 0:   name = "Monday";     break;
    case 1:   name = "Tuesday";    break;
    case 2:   name = "Wednesday";  break;
    case 3:   name = "Thursday";   break;
    case 4:   name = "Friday";     break;
    case 5:   name = "Saturday";   break;
    case 6:   name = "Sunday";     break;
    default:  name = "Error";      break;
}

return name;
}

/// Calculate Julian day number
/// @param year is the Gregorian year.
/// @param month is the Gregorian month.
/// @param day is the Gregorian day.
/// @returns Julian day number from Gregorian Calendar.
long julian_day_number(int year, int month, int day) {
return static_cast<long>((1461 * (year + 4800 + (month - 14) / 12)) / 4
+ (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12
- (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075);
}

/// Calculate Julian date
///
/// @param year is the Gregorian year.
/// @param month is the Gregorian month.
/// @param day is the Gregorian day.
/// @param hour is the hour.
/// @param minute is the minute.
/// @param sec is the second.
/// @returns The Julian date.
double julian_date(int year, int month, int day,
                int hour, int minute, int sec) {
return julian_day_number(year, month, day)
+ ((hour - 12.0) / 24.0) + (minute / 1440.0) + (sec / 86400.0);
}

/// Calculates Day of week: Mon = 0, Tue = 2, ..., Sun = 6
/// @param year is the Gregorian year.
/// @param month is the Gregorian month.
/// @param day is the Gregorian day.
/// @returns ISO weekday [0,6]
int weekday(int year, int month, int day) {
return static_cast<int>(labs(julian_day_number(year, month, day)) % 7);
}
}  // end namespace cs135

/* Sample input ***
4
2021-10-01,00:20:44,73473,13.94,1,Cereals
2021-10-02,13:04:43,96811,7.05,2,Meat
2021-10-03,04:01:10,99124,21.52,1,Fish
2021-10-03,05:55:10,39195,7.07,1,Baby food
2021-10-04,08:48:15,25453,24.91,1,Brown rice
2021-10-05,09:26:12,16656,5.24,3,Detergents
2021-10-06,13:14:10,40889,15.2,1,Personal hygiene
2021-10-07,06:20:25,67670,8.54,1,Alcoholic beverages
2021-10-08,08:54:58,87749,20.66,2,Vegetables
2021-10-09,10:02:08,61467,26.3,1,Toys

*/

/* Sample output ***
Sales Report - Saturdays

Julian Date     Stock  Department                    Price  Qty    Total
------------------------------------------------------------------------
2459490.044942  96811  Meat                        $  7.05   2  $  14.10
2459496.918148  61467  Toys                        $ 26.30   1  $  26.30

Largest quantity: 2
Largest sale:     $26.30

Total items sold: 3
Total sales:      $40.40

*/