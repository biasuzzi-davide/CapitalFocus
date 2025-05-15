#ifndef IMPORT_ERRORS_H
#define IMPORT_ERRORS_H

#include <stdexcept>
#include <QString>

// Eccezione per errori nell'apertura del file
class FileOpenError : public std::runtime_error {
public:
    // Costruttore, prende il percorso del file
    explicit FileOpenError(const QString& path)
        : std::runtime_error(("Unable to open: " + path).toStdString()) {}
};

// Eccezione per errori nel parsing JSON
class JsonParseError : public std::runtime_error {
public:
    // Costruttore, prende il messaggio di errore
    explicit JsonParseError(const QString& msg)
        : std::runtime_error(("JSON error: " + msg).toStdString()) {}
};

// Eccezione per errori nel parsing XML
class XmlParseError : public std::runtime_error {
public:
    // Costruttore, prende il messaggio di errore
    explicit XmlParseError(const QString& msg)
        : std::runtime_error(("XML error:" + msg).toStdString()) {}
};

#endif // IMPORT_ERRORS_H
