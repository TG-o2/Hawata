#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QString>

class EmailSender
{
public:
    EmailSender();

    bool sendEmail(const QString &to, const QString &subject, const QString &body);
};

#endif // EMAILSENDER_H
