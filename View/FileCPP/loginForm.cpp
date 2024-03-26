#include "../FileH/loginForm.h"
#include<QLayout>

LoginForm::LoginForm(bool registrazione, bool modifica, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* form=new QVBoxLayout(this);
    form->setAlignment(Qt::AlignLeft|Qt::AlignCenter);
    form->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* widgetLayoutpassword=new QWidget();
    QHBoxLayout* layoutpassword=new QHBoxLayout(widgetLayoutpassword);

    QWidget* widgetLayoutpassword2=new QWidget();
    QHBoxLayout* layoutpassword2=new QHBoxLayout(widgetLayoutpassword2);

    QWidget* widgetLayoutUser=new QWidget();
    QHBoxLayout* layoutuser= new QHBoxLayout(widgetLayoutUser);

    if (modifica)
    {
       QString s = QString::fromStdString("Modifica username, password o entrambi");
       labelTitle = new QLabel(s);
       form->addWidget(labelTitle);
       labelUser= new QLabel("Nuovo username");
    }
    else
    {
       labelUser= new QLabel("Username");
    }

    lineUser =new QLineEdit();
    layoutuser->addWidget(lineUser);

    if (modifica)
    {
       labelPassword= new QLabel("Nuova password");
    }
    else
    {
       labelPassword= new QLabel("Password");
    }


    linePassword=new QLineEdit();
    linePassword->setEchoMode(QLineEdit::Password);
    layoutpassword->addWidget(linePassword);

    buttonView= new QPushButton();
    buttonView->setIcon(QIcon(":Immagini/eyeIcon.png"));
    buttonView->setStyleSheet("QPushButton { background-color: white }");
    buttonView->setCheckable(true);
    layoutpassword->addWidget(buttonView);

    if (modifica)
    {
       labelConfirmPassword= new QLabel("Conferma la nuova password");
    }
    else
    {
       labelConfirmPassword= new QLabel("Conferma la password");
    }

    labelConfirmPassword->setHidden(!registrazione);

    lineConfirmPassword=new QLineEdit();
    lineConfirmPassword->setHidden(!registrazione);
    lineConfirmPassword->setEchoMode(QLineEdit::Password);
    layoutpassword2->addWidget(lineConfirmPassword);

    buttonView2= new QPushButton();
    buttonView2->setHidden(!registrazione);
    buttonView2->setIcon(QIcon(":Immagini/eyeIcon.png"));
    buttonView2->setStyleSheet("QPushButton { background-color: white }");
    buttonView2->setCheckable(true);
    layoutpassword2->addWidget(buttonView2);

    form->addWidget(labelUser);
    form->addWidget(widgetLayoutUser);
    form->addWidget(labelPassword);
    form->addWidget(widgetLayoutpassword);
    form->addWidget(labelConfirmPassword);
    form->addWidget(widgetLayoutpassword2);

    connect(buttonView, &QPushButton::clicked, this, &LoginForm::on_buttonView_toggled);
    connect(buttonView2, &QPushButton::clicked, this, &LoginForm::on_buttonView_toggled2);

}
QString LoginForm::getUser(){
    return lineUser->text();
}
QString LoginForm::getPassword(){
    return linePassword->text();
}
QString LoginForm::getConfirmPassword(){
    return lineConfirmPassword->text();
}

LoginForm::~LoginForm()
{

}

void LoginForm::on_buttonView_toggled(bool checked)
{
    if(checked){
        buttonView->setIcon(QIcon(":Immagini/notEyeIcon.png"));
        linePassword->setEchoMode(QLineEdit::Normal);
    }else{
        buttonView->setIcon(QIcon(":Immagini/eyeIcon.png"));
        linePassword->setEchoMode(QLineEdit::Password);
    }
}
void LoginForm::on_buttonView_toggled2(bool checked)
{
    if(checked){
        buttonView2->setIcon(QIcon(":Immagini/notEyeIcon.png"));
        lineConfirmPassword->setEchoMode(QLineEdit::Normal);
    }else{
        buttonView2->setIcon(QIcon(":Immagini/eyeIcon.png"));
        lineConfirmPassword->setEchoMode(QLineEdit::Password);
    }
}

