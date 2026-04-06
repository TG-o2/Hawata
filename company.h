#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QList>

class Company
{
public:
    Company();
    Company(int companyId,
            const QString &name,
            const QString &location,
            const QString &email,
            const QString &phone,
            const QString &preferredFish,
            const QString &status);

    int getCompanyId() const;
    QString getName() const;
    QString getLocation() const;
    QString getEmail() const;
    QString getPhone() const;
    QString getPreferredFish() const;
    QString getStatus() const;

    void setCompanyId(int value);
    void setName(const QString &value);
    void setLocation(const QString &value);
    void setEmail(const QString &value);
    void setPhone(const QString &value);
    void setPreferredFish(const QString &value);
    void setStatus(const QString &value);

    bool ajouter_company();
    QSqlQueryModel* afficher();
    bool supprimer(int companyId);
    bool modifier_company();
    QList<Company> afficher_liste();
    QString getLastError();

private:
    int m_companyId;
    QString m_name;
    QString m_location;
    QString m_email;
    QString m_phone;
    QString m_preferredFish;
    QString m_status; // "ACTIVE" or "INACTIVE"
};

#endif // COMPANY_H
