#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Company
{
public:
    Company();

    // Create a new company in the database
    bool createCompany(const QString &name,
                       const QString &location,
                       const QString &email,
                       const QString &phone,
                       const QString &preferredFish,
                       const QString &status);


    QSqlQueryModel* getAllCompanies();


    QSqlQueryModel* searchCompanies(const QString &searchText);


    bool updateCompany(int companyId,
                       const QString &name,
                       const QString &location,
                       const QString &email,
                       const QString &phone,
                       const QString &preferredFish,
                       const QString &status);


    bool deleteCompany(int companyId);


    QSqlQuery getCompanyById(int companyId);


    QString getLastError();

};

#endif // COMPANY_H
