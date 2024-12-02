#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

// Fonction pour convertir une latitude ou longitude de format "degrés et minutes" en degrés décimaux
double convertToDecimalDegrees(const std::string& degreesMinutes, const std::string& direction) {
    // Conversion des minutes en degrés décimaux
    double dd = std::stod(degreesMinutes.substr(0, 2)) + std::stod(degreesMinutes.substr(2)) / 60.0;

    // Si la direction est 'S' ou 'W', la valeur doit être négative
    if (direction == "S" || direction == "W") {
        dd = -dd;
    }

    return dd;
}

// Fonction pour analyser une trame NMEA de type GPGGA et renvoyer la latitude et la longitude
bool decodeGPGGA(const std::string& nmeaSentence, double& latitude, double& longitude) {
    // Vérification de la trame, elle doit commencer par "$GPGGA"
    if (nmeaSentence.substr(0, 6) != "$GPGGA") {
        std::cerr << "Trame non valide : " << nmeaSentence << std::endl;
        return false;
    }

    // Diviser la trame en champs en utilisant la virgule comme séparateur
    std::vector<std::string> fields;
    std::stringstream ss(nmeaSentence);  // Utilisation de stringstream pour découper la chaîne
    std::string field;

    // Découper la trame en fonction des virgules
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // Extraction et conversion des informations présentes dans la trame
    try {
        // 1. Latitude : champ 2 (en degrés et minutes) et champ 3 (direction : N/S)
        latitude = convertToDecimalDegrees(fields[2], fields[3]);

        // 2. Longitude : champ 4 (en degrés et minutes) et champ 5 (direction : E/W)
        longitude = convertToDecimalDegrees(fields[4], fields[5]);

    }
    catch (const std::exception& e) {
        // En cas d'erreur lors de l'extraction ou de la conversion des données
        std::cerr << "Erreur de décodage : " << e.what() << std::endl;
        return false;
    }

    return true;
}

int main() {
    // Exemple de trame GPGGA, format standard des récepteurs GPS
    std::string nmeaSentence = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";  // Exemple de trame GPGGA

    // Variables pour stocker les coordonnées extraites
    double latitude = 0.0;
    double longitude = 0.0;

    // Appel de la fonction pour décoder la trame et extraire la latitude et la longitude
    if (decodeGPGGA(nmeaSentence, latitude, longitude)) {
        // Affichage des résultats
        std::cout << "Latitude: " << latitude << "° | Longitude: " << longitude << "°" << std::endl;
    }
    else {
        std::cout << "Échec du décodage des données GPS." << std::endl;
    }

    return 0;
}
