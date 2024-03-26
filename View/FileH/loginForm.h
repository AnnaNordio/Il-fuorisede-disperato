#ifndef LOGGINFORM_H
#define LOGGINFORM_H

#include<QWidget>
#include <QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QString>


class LoginForm : public QWidget
{
    Q_OBJECT

public:

    LoginForm(bool registrazione=false, bool modifica=false, QWidget *parent = nullptr);
    QString getUser();
    QString getPassword();
    QString getConfirmPassword();
    ~LoginForm();

private slots:

     void on_buttonView_toggled(bool checked);
     void on_buttonView_toggled2(bool checked);


signals:

private:

    QLabel* labelUser;
    QLabel* labelPassword;
    QLabel* labelConfirmPassword;
    QLabel* labelTitle;
    QLineEdit* lineUser;
    QLineEdit* linePassword;
    QLineEdit* lineConfirmPassword;
    QPushButton* buttonView;
    QPushButton* buttonView2;

};

#endif // LOGGINFORM_H
