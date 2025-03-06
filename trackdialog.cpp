#include "trackdialog.h"

TrackDialog::TrackDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackDialog)
{
    ui->setupUi(this);
    ui->buttonBox->disconnect(SIGNAL(accepted()));
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TrackDialog::validateAndAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

TrackDialog::~TrackDialog() {
    delete ui;
}
//проверОчка
void TrackDialog::validateAndAccept() {
    if (ui->lineTitle->text().trimmed().isEmpty() ||
        ui->lineName->text().trimmed().isEmpty() ||
        ui->lineGenre->text().trimmed().isEmpty() ||
        ui->spinDuration->value() <= 0)
    {
        QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены, а длительность больше 0.");
        return;
    }

    QDialog::accept();
}

QString TrackDialog::getTitle() const {
    return ui->lineTitle->text();
}

QString TrackDialog::getArtist() const {
    return ui->lineName->text();
}

double TrackDialog::getDuration() const {
    return ui->spinDuration->value();
}

QString TrackDialog::getGenre() const {
    return ui->lineGenre->text();
}





void TrackDialog::setTitle(const QString &title)
{
    ui->lineTitle->setText(title);
}

void TrackDialog::setArtist(const QString &artist)
{
    ui->lineName->setText(artist);
}

void TrackDialog::setDuration(double duration)
{
    ui->spinDuration->setValue(duration);
}

void TrackDialog::setGenre(const QString &genre)
{
    ui->lineGenre->setText(genre);
}
