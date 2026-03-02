#ifndef COMPANY_H
#define COMPANY_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QList>

class CompanyRecord {
public:
    CompanyRecord() = default;
    CompanyRecord(int id,
                  const QString &name,
                  const QString &location,
                  const QString &email,
                  const QString &phone,
                  const QString &preferredFish,
                  const QString &status)
        : m_id(id),
        m_name(name),
        m_location(location),
        m_email(email),
        m_phone(phone),
        m_preferredFish(preferredFish),
        m_status(status)
    {
    }

    int id() const { return m_id; }
    const QString& name() const { return m_name; }
    const QString& location() const { return m_location; }
    const QString& email() const { return m_email; }
    const QString& phone() const { return m_phone; }
    const QString& preferredFish() const { return m_preferredFish; }
    const QString& status() const { return m_status; }

private:
    int m_id = 0;
    QString m_name;
    QString m_location;
    QString m_email;
    QString m_phone;
    QString m_preferredFish;
    QString m_status; // "active" or "inactive"
};

class Company
{
private:
    QSqlQueryModel* companiesModel;
public:
    Company();
    ~Company() {
        delete companiesModel;
    }

    bool createCompany(const QString &name,
                       const QString &location,
                       const QString &email,
                       const QString &phone,
                       const QString &preferredFish,
                       const QString &status);

    QList<CompanyRecord> getAllCompanies();
    QString getLastError();
    QSqlQueryModel* getCompaniesModel();
    bool deleteCompany(int companyId);
    bool updateCompany(int companyId,
                       const QString &name,
                       const QString &location,
                       const QString &email,
                       const QString &phone,
                       const QString &preferredFish,
                       const QString &status);
};

#endif // COMPANY_H
