
#include <iostream>
#include "curl\curl.h"
#include<string>
#include <fstream>

using namespace::std;


size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
    s->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}



void checknumber(std::string cyfra, int probanr) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        std::string url = "https://hostgier.pl/blackfriday/submit.php?password=";
        url.append(cyfra);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        std::string responseother = "<html>\n"
"<body>\n"
"\n"
"Liczba "+ cyfra +" jest \n"
"nie poprawna, probuj dalej\n"
"<br><br>Jezeli uda ci sie poprawnie wypelnic zapytanie, otrzymasz link do nastepnego kroku, powodzenia! <br>\n"
"\n"
"</body>\n"
"</html>\n"
"\n"
"";
        if (response != responseother) {
            std::cout << "Mam ta cyfre!: " << cyfra << endl;;
            system("pause");
            std::ofstream out("output.txt");
            out << response;
            out.close();
        }
        //std::cout << "To odpowiedz: " << response << endl;

    }
    curl_easy_cleanup(curl);

}

int main()
{
    int i;
    int b;
    cout << "Podaj od jakiej liczby zaczac:";
    cin >> i;
    cout << "Podaj do ilu:";
    cin >> b;
    for (i; i < b; ++i) {
        cout << "To jest proba nr: " << i << endl;
        std::string numerek = std::to_string(i);
        checknumber(numerek, i);
    }
}

