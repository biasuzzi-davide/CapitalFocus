// CreatePlaceWidget.cpp
#include "view/createplacewidget.h"
#include "ui_CreatePlaceWidget.h"
#include "controller/placecontroller.h"
#include <QComboBox>
#include <QPushButton>
#include "model/weekday.h"


CreatePlaceWidget::CreatePlaceWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreatePlaceWidget)
{
    ui->setupUi(this);
    ui->stackedWidgetDetails->setCurrentIndex(ui->comboBoxType->currentIndex());
}

void CreatePlaceWidget::showDetailPage(int index)
{
    ui->stackedWidgetDetails->setCurrentIndex(index);
}

CreatePlaceWidget::~CreatePlaceWidget()
{
    delete ui;
}

void CreatePlaceWidget::setController(PlaceController *c)
{
    controller = c;
    if (!controller) return;

    /* --- Pulsante Cancel ----------------------------------- */
    connect(ui->pushButtonCancel,  &QPushButton::clicked,
            controller,            &PlaceController::goBack);

    /* --- Pulsante Create / Save ---------------------------- */
    connect(ui->pushButtonCreate,  &QPushButton::clicked,
            controller,            &PlaceController::createNewPlace);

    /* --- Combobox “Type”  ---------------------------------- */
    connect(ui->comboBoxType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            controller,       &PlaceController::onCreateTypeChanged);
}

// ---------- getter campi comuni ------------------------------
QString CreatePlaceWidget::type() const        { return ui->comboBoxType->currentText(); }
QString CreatePlaceWidget::name() const        { return ui->lineEditName->text(); }
QString CreatePlaceWidget::city() const        { return ui->lineEditCity->text(); }
QString CreatePlaceWidget::description() const { return ui->textEditDescription->toPlainText(); }
double  CreatePlaceWidget::rating() const      { return ui->spinBoxRating->value(); }
double  CreatePlaceWidget::cost() const        { return ui->spinBoxCost->value(); }

// ---------- setter campi comuni ------------------------------
void CreatePlaceWidget::setType(const QString &type) {
    int idx = ui->comboBoxType->findText(type);
    if (idx != -1) ui->comboBoxType->setCurrentIndex(idx);
}
void CreatePlaceWidget::setName(const QString &name)     { ui->lineEditName->setText(name); }
void CreatePlaceWidget::setCity(const QString &city)     { ui->lineEditCity->setText(city); }
void CreatePlaceWidget::setDescription(const QString &description) { ui->textEditDescription->setPlainText(description); }
void CreatePlaceWidget::setRating(double rating)         { ui->spinBoxRating->setValue(rating); }
void CreatePlaceWidget::setCost(double cost)             { ui->spinBoxCost->setValue(cost); }

// ---------- Disco --------------------------------------------
QString CreatePlaceWidget::musicGenre() const  { return ui->lineEditMusicGenre->text(); }
bool    CreatePlaceWidget::prive() const       { return ui->checkBoxPrive->isChecked(); }
QString CreatePlaceWidget::dressCode() const   { return ui->lineEditDressCode->text(); }
void    CreatePlaceWidget::setMusicGenre(const QString &genre) { ui->lineEditMusicGenre->setText(genre); }
void    CreatePlaceWidget::setPrive(bool prive)             { ui->checkBoxPrive->setChecked(prive); }
void    CreatePlaceWidget::setDressCode(const QString &code){ ui->lineEditDressCode->setText(code); }

// ---------- PanoramicPoints ----------------------------------
double  CreatePlaceWidget::altitude() const        { return ui->spinBoxAltitude->value(); }
bool    CreatePlaceWidget::binoculars() const      { return ui->checkBoxBinoculars->isChecked(); }
bool    CreatePlaceWidget::nightLighting() const   { return ui->checkBoxNightLighting->isChecked(); }
void    CreatePlaceWidget::setAltitude(double altitude)       { ui->spinBoxAltitude->setValue(altitude); }
void    CreatePlaceWidget::setBinoculars(bool binoculars)     { ui->checkBoxBinoculars->setChecked(binoculars); }
void    CreatePlaceWidget::setNightLighting(bool nightLighting){ ui->checkBoxNightLighting->setChecked(nightLighting); }

// ---------- Cafe ---------------------------------------------
bool    CreatePlaceWidget::terrace() const        { return ui->checkBoxTerrace->isChecked(); }
QString CreatePlaceWidget::specialDrink() const   { return ui->lineEditSpecialDrink->text(); }
void    CreatePlaceWidget::setTerrace(bool terrace)           { ui->checkBoxTerrace->setChecked(terrace); }
void    CreatePlaceWidget::setSpecialDrink(const QString &drink){ ui->lineEditSpecialDrink->setText(drink); }

// ---------- Restaurant ---------------------------------------
QString CreatePlaceWidget::cuisineType() const       { return ui->lineEditCuisine->text(); }
bool    CreatePlaceWidget::reservationNeeded() const { return ui->checkBoxReservation->isChecked(); }
QString CreatePlaceWidget::specialDish() const       { return ui->lineEditSpecialDish->text(); }
void    CreatePlaceWidget::setCuisineType(const QString &cuisine) { ui->lineEditCuisine->setText(cuisine); }
void    CreatePlaceWidget::setReservationNeeded(bool needed)    { ui->checkBoxReservation->setChecked(needed); }
void    CreatePlaceWidget::setSpecialDish(const QString &dish){ ui->lineEditSpecialDish->setText(dish); }

// ---------- Mall ---------------------------------------------
int     CreatePlaceWidget::shopCount() const     { return ui->spinBoxShopCount->value(); }
bool    CreatePlaceWidget::cinema() const        { return ui->checkBoxCinema->isChecked(); }
bool    CreatePlaceWidget::freeParking() const   { return ui->checkBoxParking->isChecked(); }
void    CreatePlaceWidget::setShopCount(int count)        { ui->spinBoxShopCount->setValue(count); }
void    CreatePlaceWidget::setCinema(bool cinema)         { ui->checkBoxCinema->setChecked(cinema); }
void    CreatePlaceWidget::setFreeParking(bool freeParking){ ui->checkBoxParking->setChecked(freeParking); }

// ---------- LocalMarket --------------------------------------
bool    CreatePlaceWidget::artisans() const      { return ui->checkBoxArtisans->isChecked(); }
bool    CreatePlaceWidget::seasonal() const      { return ui->checkBoxSeasonal->isChecked(); }
QString CreatePlaceWidget::period() const        { return ui->lineEditPeriod->text(); }
void    CreatePlaceWidget::setArtisans(bool artisans)    { ui->checkBoxArtisans->setChecked(artisans); }
void    CreatePlaceWidget::setSeasonal(bool seasonal)    { ui->checkBoxSeasonal->setChecked(seasonal); }
void    CreatePlaceWidget::setPeriod(const QString &period) { ui->lineEditPeriod->setText(period); }

// ---------- Museum -------------------------------------------
bool    CreatePlaceWidget::audioGuide() const      { return ui->checkBoxAudioGuide->isChecked(); }
void    CreatePlaceWidget::setAudioGuide(bool audio)        { ui->checkBoxAudioGuide->setChecked(audio); }

// ---------- Monument -----------------------------------------
bool    CreatePlaceWidget::unesco() const              { return ui->checkBoxUnesco->isChecked(); }
QString CreatePlaceWidget::conservationStatus() const  { return ui->lineEditConservation->text(); }
bool    CreatePlaceWidget::openToPublic() const        { return ui->checkBoxOpenToPublic->isChecked(); }
void    CreatePlaceWidget::setUnesco(bool unesco)              { ui->checkBoxUnesco->setChecked(unesco); }
void    CreatePlaceWidget::setConservationStatus(const QString &status){ ui->lineEditConservation->setText(status); }
void    CreatePlaceWidget::setOpenToPublic(bool open)        { ui->checkBoxOpenToPublic->setChecked(open); }

// ---------- Orari --------------------------------------------
CreatePlaceWidget::DayHours CreatePlaceWidget::hours(Weekday day) const
{
    DayHours h;
    switch (day) {
    case Weekday::Monday:
        h.open          = ui->timeEditMondayOpen->time();
        h.close         = ui->timeEditMondayClose->time();
        h.alwaysOpen    = ui->checkBoxMondayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxMondayAlwaysClosed->isChecked();
        break;
    case Weekday::Tuesday:
        h.open          = ui->timeEditTuesdayOpen->time();
        h.close         = ui->timeEditTuesdayClose->time();
        h.alwaysOpen    = ui->checkBoxTuesdayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxTuesdayAlwaysClosed->isChecked();
        break;
    case Weekday::Wednesday:
        h.open          = ui->timeEditWednesdayOpen->time();
        h.close         = ui->timeEditWednesdayClose->time();
        h.alwaysOpen    = ui->checkBoxWednesdayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxWednesdayAlwaysClosed->isChecked();
        break;
    case Weekday::Thursday:
        h.open          = ui->timeEditThursdayOpen->time();
        h.close         = ui->timeEditThursdayClose->time();
        h.alwaysOpen    = ui->checkBoxThursdayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxThursdayAlwaysClosed->isChecked();
        break;
    case Weekday::Friday:
        h.open          = ui->timeEditFridayOpen->time();
        h.close         = ui->timeEditFridayClose->time();
        h.alwaysOpen    = ui->checkBoxFridayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxFridayAlwaysClosed->isChecked();
        break;
    case Weekday::Saturday:
        h.open          = ui->timeEditSaturdayOpen->time();
        h.close         = ui->timeEditSaturdayClose->time();
        h.alwaysOpen    = ui->checkBoxSaturdayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxSaturdayAlwaysClosed->isChecked();
        break;
    case Weekday::Sunday:
        h.open          = ui->timeEditSundayOpen->time();
        h.close         = ui->timeEditSundayClose->time();
        h.alwaysOpen    = ui->checkBoxSundayAlwaysOpen->isChecked();
        h.alwaysClosed  = ui->checkBoxSundayAlwaysClosed->isChecked();
        break;
    default:
        // nessuna azione
        break;
    }
    return h;
}
void CreatePlaceWidget::setHours(Weekday day, const CreatePlaceWidget::DayHours &h)
{
    switch (day) {
    case Weekday::Monday:
        ui->timeEditMondayOpen->setTime(h.open);
        ui->timeEditMondayClose->setTime(h.close);
        ui->checkBoxMondayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxMondayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Tuesday:
        ui->timeEditTuesdayOpen->setTime(h.open);
        ui->timeEditTuesdayClose->setTime(h.close);
        ui->checkBoxTuesdayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxTuesdayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Wednesday:
        ui->timeEditWednesdayOpen->setTime(h.open);
        ui->timeEditWednesdayClose->setTime(h.close);
        ui->checkBoxWednesdayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxWednesdayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Thursday:
        ui->timeEditThursdayOpen->setTime(h.open);
        ui->timeEditThursdayClose->setTime(h.close);
        ui->checkBoxThursdayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxThursdayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Friday:
        ui->timeEditFridayOpen->setTime(h.open);
        ui->timeEditFridayClose->setTime(h.close);
        ui->checkBoxFridayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxFridayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Saturday:
        ui->timeEditSaturdayOpen->setTime(h.open);
        ui->timeEditSaturdayClose->setTime(h.close);
        ui->checkBoxSaturdayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxSaturdayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    case Weekday::Sunday:
        ui->timeEditSundayOpen->setTime(h.open);
        ui->timeEditSundayClose->setTime(h.close);
        ui->checkBoxSundayAlwaysOpen->setChecked(h.alwaysOpen);
        ui->checkBoxSundayAlwaysClosed->setChecked(h.alwaysClosed);
        break;
    default:
        // nessuna azione
        break;
    }
}
// === Entertainment ===
QTime CreatePlaceWidget::averageStay_Disco() const { return ui->averageStayTimeEdit->time();}
int CreatePlaceWidget::minimumAge_Disco() const {return ui->minimumAgeSpinBox->value();}
QString CreatePlaceWidget::restrictedEntry_Disco() const {
    return ui->restrictedEntryLineEdit->text();
}

void CreatePlaceWidget::setAverageStay_Disco(const QTime &time) {
    ui->averageStayTimeEdit->setTime(time);
}
void CreatePlaceWidget::setMinimumAge_Disco(int age) {
    ui->minimumAgeSpinBox->setValue(age);
}
void CreatePlaceWidget::setRestrictedEntry_Disco(const QString &entry) {
    ui->restrictedEntryLineEdit->setText(entry);
}


QTime CreatePlaceWidget::averageStay_Panoramic() const {
    return ui->averageStayTimeEdit_2->time();
}
int CreatePlaceWidget::minimumAge_Panoramic() const {
    return ui->minimumAgeSpinBox_2->value();
}
QString CreatePlaceWidget::restrictedEntry_Panoramic() const {
    return ui->restrictedEntryLineEdit_2->text();
}

void CreatePlaceWidget::setAverageStay_Panoramic(const QTime &time) {
    ui->averageStayTimeEdit_2->setTime(time);
}
void CreatePlaceWidget::setMinimumAge_Panoramic(int age) {
    ui->minimumAgeSpinBox_2->setValue(age);
}
void CreatePlaceWidget::setRestrictedEntry_Panoramic(const QString &entry) {
    ui->restrictedEntryLineEdit_2->setText(entry);
}

// === Food ===
bool CreatePlaceWidget::takeAway_Restaurant() const {
    return ui->takeAwayCheckBox->isChecked();
}
QTime CreatePlaceWidget::averageWaitingTime_Restaurant() const {
    return ui->averageWaitingTimeTimeEdit->time();
}
bool CreatePlaceWidget::veganMenu_Restaurant() const {
    return ui->veganMenuCheckBox->isChecked();
}

void CreatePlaceWidget::setTakeAway_Restaurant(bool takeAway) {
    ui->takeAwayCheckBox->setChecked(takeAway);
}
void CreatePlaceWidget::setAverageWaitingTime_Restaurant(const QTime &time) {
    ui->averageWaitingTimeTimeEdit->setTime(time);
}
void CreatePlaceWidget::setVeganMenu_Restaurant(bool vegan) {
    ui->veganMenuCheckBox->setChecked(vegan);
}


bool CreatePlaceWidget::takeAway_Cafe() const {
    return ui->takeAwayCheckBox_2->isChecked();
}
QTime CreatePlaceWidget::averageWaitingTime_Cafe() const {
    return ui->averageWaitingTimeTimeEdit_2->time();
}
bool CreatePlaceWidget::veganMenu_Cafe() const {
    return ui->veganMenuCheckBox_2->isChecked();
}

void CreatePlaceWidget::setTakeAway_Cafe(bool takeAway) {
    ui->takeAwayCheckBox_2->setChecked(takeAway);
}
void CreatePlaceWidget::setAverageWaitingTime_Cafe(const QTime &time) {
    ui->averageWaitingTimeTimeEdit_2->setTime(time);
}
void CreatePlaceWidget::setVeganMenu_Cafe(bool vegan) {
    ui->veganMenuCheckBox_2->setChecked(vegan);
}

// === Culture ===
double CreatePlaceWidget::studentDiscount_Museum() const {
    return ui->spinBoxStudentDiscount->value();
}
bool CreatePlaceWidget::guidedTour_Museum() const {
    return ui->checkBoxGuided->isChecked();
}
QString CreatePlaceWidget::culturalFocus_Museum() const {
    return ui->lineEditCulturalFocus->text();
}

void CreatePlaceWidget::setStudentDiscount_Museum(double discount) {
    ui->spinBoxStudentDiscount->setValue(discount);
}
void CreatePlaceWidget::setGuidedTour_Museum(bool guided) {
    ui->checkBoxGuided->setChecked(guided);
}
void CreatePlaceWidget::setCulturalFocus_Museum(const QString &focus) {
    ui->lineEditCulturalFocus->setText(focus);
}

double CreatePlaceWidget::studentDiscount_Monument() const {
    return ui->spinBoxStudentDiscount_2->value();
}
bool CreatePlaceWidget::guidedTour_Monument() const {
    return ui->checkBoxGuided_2->isChecked();
}
QString CreatePlaceWidget::culturalFocus_Monument() const {
    return ui->lineEditCulturalFocus_2->text();
}

void CreatePlaceWidget::setStudentDiscount_Monument(double discount) {
    ui->spinBoxStudentDiscount_2->setValue(discount);
}
void CreatePlaceWidget::setGuidedTour_Monument(bool guided) {
    ui->checkBoxGuided_2->setChecked(guided);
}
void CreatePlaceWidget::setCulturalFocus_Monument(const QString &focus) {
    ui->lineEditCulturalFocus_2->setText(focus);
}

// === Shopping ===
bool CreatePlaceWidget::outdoor_Market() const {
    return ui->outdoorCheckBox->isChecked();
}
bool CreatePlaceWidget::foodArea_Market() const {
    return ui->foodAreaCheckBox->isChecked();
}
int CreatePlaceWidget::standNumber_Market() const {
    return ui->standNumberSpinBox->value();
}

void CreatePlaceWidget::setOutdoor_Market(bool outdoor) {
    ui->outdoorCheckBox->setChecked(outdoor);
}
void CreatePlaceWidget::setFoodArea_Market(bool hasFoodArea) {
    ui->foodAreaCheckBox->setChecked(hasFoodArea);
}
void CreatePlaceWidget::setStandNumber_Market(int num) {
    ui->standNumberSpinBox->setValue(num);
}



bool CreatePlaceWidget::outdoor_Mall() const {
    return ui->outdoorCheckBox_2->isChecked();
}
bool CreatePlaceWidget::foodArea_Mall() const {
    return ui->foodAreaCheckBox_2->isChecked();
}
int CreatePlaceWidget::standNumber_Mall() const {
    return ui->standNumberSpinBox_2->value();
}

void CreatePlaceWidget::setOutdoor_Mall(bool outdoor) {
    ui->outdoorCheckBox_2->setChecked(outdoor);
}
void CreatePlaceWidget::setFoodArea_Mall(bool hasFoodArea) {
    ui->foodAreaCheckBox_2->setChecked(hasFoodArea);
}
void CreatePlaceWidget::setStandNumber_Mall(int num) {
    ui->standNumberSpinBox_2->setValue(num);
}

int CreatePlaceWidget::getTypeIndex() const {
    return ui->comboBoxType->currentIndex();
}
void CreatePlaceWidget::setEditing(bool enabled)
{
    m_editing = enabled;
    ui->pushButtonCreate->setText(enabled ? tr("Save") : tr("Create"));
}

bool CreatePlaceWidget::isEditing() const
{
    return m_editing;
}
void CreatePlaceWidget::resetFields()
{
    /* ---------- campi comuni ---------- */
    ui->comboBoxType->setCurrentIndex(0);
    ui->lineEditName->clear();
    ui->lineEditCity->clear();
    ui->textEditDescription->clear();
    ui->spinBoxRating->setValue(0.0);
    ui->spinBoxCost->setValue(0.0);

    /* ---------- Disco ---------- */
    ui->lineEditMusicGenre->clear();
    ui->checkBoxPrive->setChecked(false);
    ui->lineEditDressCode->clear();
    ui->averageStayTimeEdit->setTime(QTime(0,0));
    ui->minimumAgeSpinBox->setValue(0);
    ui->restrictedEntryLineEdit->clear();

    /* ---------- PanoramicPoints ---------- */
    ui->spinBoxAltitude->setValue(0.0);
    ui->checkBoxBinoculars->setChecked(false);
    ui->checkBoxNightLighting->setChecked(false);
    ui->averageStayTimeEdit_2->setTime(QTime(0,0));
    ui->minimumAgeSpinBox_2->setValue(0);
    ui->restrictedEntryLineEdit_2->clear();

    /* ---------- Cafe ---------- */
    ui->checkBoxTerrace->setChecked(false);
    ui->lineEditSpecialDrink->clear();
    ui->takeAwayCheckBox_2->setChecked(false);
    ui->averageWaitingTimeTimeEdit_2->setTime(QTime(0,0));
    ui->veganMenuCheckBox_2->setChecked(false);

    /* ---------- Restaurant ---------- */
    ui->takeAwayCheckBox->setChecked(false);
    ui->averageWaitingTimeTimeEdit->setTime(QTime(0,0));
    ui->veganMenuCheckBox->setChecked(false);
    ui->lineEditCuisine->clear();
    ui->checkBoxReservation->setChecked(false);
    ui->lineEditSpecialDish->clear();

    /* ---------- Mall ---------- */
    ui->outdoorCheckBox_2->setChecked(false);
    ui->foodAreaCheckBox_2->setChecked(false);
    ui->standNumberSpinBox_2->setValue(0);
    ui->spinBoxShopCount->setValue(0);
    ui->checkBoxCinema->setChecked(false);
    ui->checkBoxParking->setChecked(false);

    /* ---------- LocalMarket ---------- */
    ui->outdoorCheckBox->setChecked(false);
    ui->foodAreaCheckBox->setChecked(false);
    ui->standNumberSpinBox->setValue(0);
    ui->checkBoxArtisans->setChecked(false);
    ui->checkBoxSeasonal->setChecked(false);
    ui->lineEditPeriod->clear();

    /* ---------- Museum ---------- */
    ui->spinBoxStudentDiscount->setValue(0.0);
    ui->checkBoxGuided->setChecked(false);
    ui->lineEditCulturalFocus->clear();
    ui->checkBoxAudioGuide->setChecked(false);

    /* ---------- Monument ---------- */
    ui->spinBoxStudentDiscount_2->setValue(0.0);
    ui->checkBoxGuided_2->setChecked(false);
    ui->lineEditCulturalFocus_2->clear();
    ui->checkBoxUnesco->setChecked(false);
    ui->lineEditConservation->clear();
    ui->checkBoxOpenToPublic->setChecked(false);

    /* ---------- Orari ---------- */
    auto resetDay = [](QTimeEdit* o, QTimeEdit* c,
                       QCheckBox* alwaysOpen, QCheckBox* alwaysClosed)
    {
        o->setTime(QTime(0,0));
        c->setTime(QTime(0,0));
        alwaysOpen->setChecked(false);
        alwaysClosed->setChecked(false);
    };
    resetDay(ui->timeEditMondayOpen,    ui->timeEditMondayClose,
             ui->checkBoxMondayAlwaysOpen,    ui->checkBoxMondayAlwaysClosed);
    resetDay(ui->timeEditTuesdayOpen,   ui->timeEditTuesdayClose,
             ui->checkBoxTuesdayAlwaysOpen,   ui->checkBoxTuesdayAlwaysClosed);
    resetDay(ui->timeEditWednesdayOpen, ui->timeEditWednesdayClose,
             ui->checkBoxWednesdayAlwaysOpen, ui->checkBoxWednesdayAlwaysClosed);
    resetDay(ui->timeEditThursdayOpen,  ui->timeEditThursdayClose,
             ui->checkBoxThursdayAlwaysOpen,  ui->checkBoxThursdayAlwaysClosed);
    resetDay(ui->timeEditFridayOpen,    ui->timeEditFridayClose,
             ui->checkBoxFridayAlwaysOpen,    ui->checkBoxFridayAlwaysClosed);
    resetDay(ui->timeEditSaturdayOpen,  ui->timeEditSaturdayClose,
             ui->checkBoxSaturdayAlwaysOpen,  ui->checkBoxSaturdayAlwaysClosed);
    resetDay(ui->timeEditSundayOpen,    ui->timeEditSundayClose,
             ui->checkBoxSundayAlwaysOpen,    ui->checkBoxSundayAlwaysClosed);

    /* ---------- stato ---------- */
    setEditing(false);                  // torna in modalità “crea”
    ui->stackedWidgetDetails->setCurrentIndex(0);
}
