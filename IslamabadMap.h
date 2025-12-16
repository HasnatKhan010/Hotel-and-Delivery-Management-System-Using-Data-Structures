#ifndef ISLAMABADMAP_H
#define ISLAMABADMAP_H

#include <iostream>
#include <string>
#include <vector>
#include "Display.h"

using namespace std;

class IslamabadMap {
public:
    static void displayMap(string highlightSector = "") {
        // ASCII-compatible map of Islamabad
        vector<string> mapLines = {
            "===============================================================================",
            "                    ISLAMABAD - THE CAPITAL CITY OF PAKISTAN",
            "===============================================================================",
            "",
            "                          ___Margalla Hills National Park___",
            "                     ^^^^\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\^^^^",
            "                ^^^^\\/\\/\\  Daman-e-Koh  /\\  Monal  /\\/\\/\\/^^^^",
            "           ^^^^\\/\\/\\/\\/\\/\\ [VIEW]Point  [REST]aurant /\\/\\/\\/^^^^",
            "      ^^^^\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\^^^^",
            "    ^^^^\\/\\/\\/  Trail-3  /\\  Trail-5  /\\  Pir Sohawa  /\\/\\/\\^^^^",
            "    =============================================================================",
            "",
            "                            [ZONE I - DIPLOMATIC ENCLAVE]",
            "    +------------------------------------------------------------------------+",
            "    | [GOV] Embassies | [GOV] Foreign   |   Pakistan      | Ministry of    |",
            "    |  & Consulates   |   Missions      |   Monument[MON] | Foreign Affairs|",
            "    +------------------------------------------------------------------------+",
            "",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   E-7     |   E-8     |   E-9     |   E-10    |   E-11    |",
            "    |           |           |           |           | [B]Jinnah |",
            "    | Lal Masjid|           |           |Parade Grnd| Super Mkt |",
            "    |   [M]     |           |           |           |           |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   F-5     |   F-6     |   F-7     |   F-8     |   F-9     |",
            "    |           | [GOV]Super|  Jinnah   | Blue Area |  Fatima   |",
            "    |           |  Market   | Avenue    | [B][B][B] |  Jinnah   |",
            "    |           | Islamabad |  Mall     |           |  Park [P] |",
            "    |           | Serena[H] |           |           |           |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   G-5     |   G-6     |   G-7     |   G-8     |   G-9     |",
            "    |           | [G] Golf  |  Melody   |  Karachi  |  Kashmir  |",
            "    |           |   Club    | Food Park | Company[R]|  Highway  |",
            "    |           |           |           |           |  =======  |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   H-8     |   H-9     |   H-10    |   H-11    |   H-12    |",
            "    |           |           |           |           |           |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   I-8     |   I-9     |   I-10    |   I-11    |   I-12    |",
            "    |           |           | [B] Fed.  |           |           |",
            "    |  Markaz   |           | Govt Bldgs|           |           |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |  SECTOR   |",
            "    |   I-14    |   I-15    |   I-16    |   G-10    |   G-11    |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "",
            "    ===================== CONSTITUTIONAL AVENUE =======================",
            "    [GOV]         [GOV]           [GOV]          [GOV]         [GOV]",
            "   Supreme     Parliament      President       Prime        Aiwan-e-",
            "   Court         House          House        Minister        Sadr",
            "                                 [*]         Secretariat",
            "",
            "    ====================================================================",
            "",
            "    +------------------------------------------------------------------+",
            "    |                 [U] QUAID-I-AZAM UNIVERSITY [U]                  |",
            "    |                                                                  |",
            "    |  [EDU] Campus     [P] Gardens    [EDU] Faculties   [LIB] Library |",
            "    +------------------------------------------------------------------+",
            "",
            "         +--------------------------------------------------------+",
            "         |                   [M] FAISAL MOSQUE [M]                 |",
            "         |          (One of the largest mosques in the world)      |",
            "         |                          *                              |",
            "         |                       [M] | [M]                         |",
            "         |                      /    |    \\                        |",
            "         |                   [M]    [M]    [M]                     |",
            "         |              Shah Faisal Avenue                         |",
            "         |                   ==========                            |",
            "         +--------------------------------------------------------+",
            "",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "    |           |           |           |           |           |",
            "    | PWD Area  |           | Bari Imam |           |   Rawal   |",
            "    |           |           |   [M]     |           |    Dam    |",
            "    |           |           |           |           |   ~~~~~   |",
            "    | Rawalpindi|  Sector   |  Airport  | Park Road |  ~~~~~~   |",
            "    |  Border   |  Adjacent | [AIR]IIAP |           |  Lake ~~  |",
            "    |  =======  |           |           |           |   ~~~~~   |",
            "    +-----------+-----------+-----------+-----------+-----------+",
            "",
            "===============================================================================",
            "",
            "LEGEND:",
            "[GOV] = Government Buildings/Embassies    [M] = Mosques         [B] = Commercial",
            "[P] = Parks & Green Spaces                [H] = Hotels          [AIR] = Airport",
            "[VIEW] = Hills/Viewpoints                 [MON] = Monuments     ~~~ = Water",
            "[U]/[EDU] = Educational                   [R] = Restaurants     [G] = Recreation",
            "[LIB] = Library                           [*] = Landmarks       [REST] = Restaurant",
            "",
            "KEY FEATURES:",
            "* Grid System: Sectors organized in alphabetical (E-I) and numerical pattern",
            "* Margalla Hills: Northern boundary with scenic viewpoints and trails",
            "* Blue Area: Central business district in F-6 and F-7",
            "* Constitutional Avenue: Houses all major government buildings",
            "* Faisal Mosque: Iconic landmark, one of the largest mosques globally",
            "* Rawal Dam: Eastern water reservoir and recreational area",
            "",
            "==============================================================================="
        };

        for (const string& line : mapLines) {
            if (highlightSector != "" && line.find(highlightSector) != string::npos) {
                size_t pos = line.find(highlightSector);
                if (pos != string::npos) {
                    cout << line.substr(0, pos);
                    Display::setColor(12); // Red for highlight
                    cout << highlightSector;
                    Display::setColor(7); // Reset to white
                    cout << line.substr(pos + highlightSector.length()) << endl;
                } else {
                    cout << line << endl;
                }
            } else {
                cout << line << endl;
            }
        }
    }
};

#endif
