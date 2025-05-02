#ifndef IMPORT_ERRORS_H
#define IMPORT_ERRORS_H

// errors.h
#include <stdexcept>
#include <QString>

class FileOpenError : public std::runtime_error {
public:
    explicit FileOpenError(const QString& path)
        : std::runtime_error(("Unable to open: " + path).toStdString()) {}
};

class JsonParseError : public std::runtime_error {
public:
    explicit JsonParseError(const QString& msg)
        : std::runtime_error(("JSON error: " + msg).toStdString()) {}
};

class XmlParseError : public std::runtime_error {
public:
    explicit XmlParseError(const QString& msg)
        : std::runtime_error(("XML error:" + msg).toStdString()) {}
};

#endif // IMPORT_ERRORS_H
