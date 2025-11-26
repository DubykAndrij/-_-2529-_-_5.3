#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

double calculate_z(const double x)
{
    double sin_x = sin(x);
    double sin_sq_x = sin_x * sin_x;

    if (abs(x) >= 1.0)
    {
        double numerator = cos(x) + 1.0;
        double denominator = sin_sq_x + exp(x);

        if (denominator == 0.0)
        {
            return NAN;
        }
        return numerator / denominator;
    }
    else
    {
        double S = 1.0;
        double a_j = 1.0;

        for (int j = 1; j <= 7; ++j)
        {
            double R_j = -x / j;
            a_j *= R_j;

            S += a_j;
        }

        return S / exp(x);
    }
}


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    double k_start, k_end;
    int n;

    cout << "===== ¬веденн€ параметр≥в =====" << endl;
    cout << "¬вед≥ть початкове k (k_поч): ";
    if (!(cin >> k_start)) return 1;
    cout << "¬вед≥ть к≥нцеве k (k_к≥н): ";
    if (!(cin >> k_end)) return 1;
    cout << "¬вед≥ть к≥льк≥сть в≥др≥зк≥в (n): ";
    if (!(cin >> n) || n <= 0)
    {
        cerr << "ѕомилка:  ≥льк≥сть в≥др≥зк≥в маЇ бути додатним ц≥лим числом." << endl;
        return 1;
    }

    if (k_start > k_end)
    {
        cerr << "ѕомилка: k_поч не може бути б≥льшим за k_к≥н." << endl;
        return 1;
    }

    double dk = (k_end - k_start) / n;

    cout << "\n" << endl;

    const int K_WIDTH = 18;
    const int E_K_WIDTH = 45;
    const int TOTAL_WIDTH = K_WIDTH + E_K_WIDTH + 3;

    cout << setw(TOTAL_WIDTH) << setfill('=') << "=" << endl;
    cout << setfill(' ');
    cout << "       “јЅЋ»÷я «Ќј„≈Ќ№ ¬»–ј«” E(k)       " << endl;
    cout << setw(TOTAL_WIDTH) << setfill('=') << "=" << endl;

    cout << setfill(' ');
    cout << "| " << setw(K_WIDTH - 1) << "k" << " | " << setw(E_K_WIDTH - 1) << "E(k) = z(2k+1) - z^2(2k-1) + sqrt(z(k))" << " |" << endl;
    cout << setw(TOTAL_WIDTH) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    double k = k_start;
    const double epsilon = 1e-9;

    cout << fixed << setprecision(10);

    for (int i = 0; i <= n; ++i)
    {
        if (i == n) k = k_end;

        double arg1 = 2.0 * k + 1.0;
        double arg2 = 2.0 * k - 1.0;
        double arg3 = k;

        double z1 = calculate_z(arg1);
        double z2 = calculate_z(arg2);
        double z3 = calculate_z(arg3);

        double E_k;
        string E_k_str;

        if (z3 < 0.0)
        {
            E_k_str = "ѕомилка: z(k) < 0";
            E_k = NAN;
        }
        else if (isnan(z1) || isnan(z2) || isnan(z3))
        {
            E_k_str = "ѕомилка обчисленн€ z(x)";
            E_k = NAN;
        }
        else
        {
            E_k = z1 - z2 * z2 + sqrt(z3);

            stringstream ss;
            ss << fixed << setprecision(10) << E_k;
            E_k_str = ss.str();
        }

        if (E_k_str.length() > E_K_WIDTH - 1) {
            E_k_str = E_k_str.substr(0, E_K_WIDTH - 1);
        }

        cout << "| " << setw(K_WIDTH - 1) << k << " | " << setw(E_K_WIDTH - 1) << E_k_str << " |" << endl;

        if (i < n) k += dk;
    }

    cout << setw(TOTAL_WIDTH) << setfill('-') << "-" << endl;

    return 0;
}