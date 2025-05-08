// CreatePlaceWidget.h
#include "model/weekday.h"
#ifndef CREATEPLACEWIDGET_H
#define CREATEPLACEWIDGET_H

#include <QWidget>
#include <QTime>

namespace Ui { class CreatePlaceWidget; }
class PlaceController;             // forward

class CreatePlaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CreatePlaceWidget(QWidget *parent = nullptr);
    ~CreatePlaceWidget() override;

    // Iniettiamo il controller dall'esterno
    void setController(PlaceController *c);

    // ============ getter campi comuni ============
    QString type()        const;
    QString name()        const;
    QString city()        const;
    QString description() const;
    double  rating()      const;
    double  cost()        const;

    // ============ setter campi comuni ============
    void setType(const QString &type);
    void setName(const QString &name);
    void setCity(const QString &city);
    void setDescription(const QString &description);
    void setRating(double rating);
    void setCost(double cost);

    // ============ getter & setter Disco ============
    QString musicGenre()  const;
    bool    prive()       const;
    QString dressCode()   const;
    void    setMusicGenre(const QString &genre);
    void    setPrive(bool prive);
    void    setDressCode(const QString &code);

    // ============ getter & setter PanoramicPoints ============
    double  altitude()       const;
    bool    binoculars()     const;
    bool    nightLighting()  const;
    void    setAltitude(double altitude);
    void    setBinoculars(bool binoculars);
    void    setNightLighting(bool nightLighting);

    // ============ getter & setter Cafe ============
    bool    terrace()        const;
    QString specialDrink()   const;
    void    setTerrace(bool terrace);
    void    setSpecialDrink(const QString &drink);

    // ============ getter & setter Restaurant ============
    QString cuisineType()       const;
    bool    reservationNeeded() const;
    QString specialDish()       const;
    void    setCuisineType(const QString &cuisine);
    void    setReservationNeeded(bool needed);
    void    setSpecialDish(const QString &dish);

    // ============ getter & setter Mall ============
    int     shopCount()     const;
    bool    cinema()        const;
    bool    freeParking()   const;
    void    setShopCount(int count);
    void    setCinema(bool cinema);
    void    setFreeParking(bool freeParking);

    // ============ getter & setter Local Market ============
    bool    artisans()      const;
    bool    seasonal()      const;
    QString period()        const;
    void    setArtisans(bool artisans);
    void    setSeasonal(bool seasonal);
    void    setPeriod(const QString &period);

    // ============ getter & setter Museum ============
    bool    audioGuide()      const;
    void    setAudioGuide(bool audio);

    // ============ getter & setter Monument ============
    bool    unesco()              const;
    QString conservationStatus()  const;
    bool    openToPublic()        const;
    void    setUnesco(bool unesco);
    void    setConservationStatus(const QString &status);
    void    setOpenToPublic(bool open);

    // === Entertainment ===
    QTime   averageStay_Disco() const;
    int     minimumAge_Disco() const;
    QString restrictedEntry_Disco() const;
    void    setAverageStay_Disco(const QTime &time);
    void    setMinimumAge_Disco(int age);
    void    setRestrictedEntry_Disco(const QString &entry);

    QTime   averageStay_Panoramic() const;
    int     minimumAge_Panoramic() const;
    QString restrictedEntry_Panoramic() const;
    void    setAverageStay_Panoramic(const QTime &time);
    void    setMinimumAge_Panoramic(int age);
    void    setRestrictedEntry_Panoramic(const QString &entry);
    // === Food ===
    bool    takeAway_Restaurant() const;
    QTime   averageWaitingTime_Restaurant() const;
    bool    veganMenu_Restaurant() const;
    void    setTakeAway_Restaurant(bool takeAway);
    void    setAverageWaitingTime_Restaurant(const QTime &time);
    void    setVeganMenu_Restaurant(bool vegan);

    bool    takeAway_Cafe() const;
    QTime   averageWaitingTime_Cafe() const;
    bool    veganMenu_Cafe() const;
    void    setTakeAway_Cafe(bool takeAway);
    void    setAverageWaitingTime_Cafe(const QTime &time);
    void    setVeganMenu_Cafe(bool vegan);

    // === Culture ===
    double  studentDiscount_Museum() const;
    bool    guidedTour_Museum() const;
    QString culturalFocus_Museum() const;
    void    setStudentDiscount_Museum(double discount);
    void    setGuidedTour_Museum(bool guided);
    void    setCulturalFocus_Museum(const QString &focus);

    double  studentDiscount_Monument() const;
    bool    guidedTour_Monument() const;
    QString culturalFocus_Monument() const;
    void    setStudentDiscount_Monument(double discount);
    void    setGuidedTour_Monument(bool guided);
    void    setCulturalFocus_Monument(const QString &focus);

    // === Shopping ===
    bool    outdoor_Mall() const;
    bool    foodArea_Mall() const;
    int     standNumber_Mall() const;
    void    setOutdoor_Mall(bool outdoor);
    void    setFoodArea_Mall(bool hasFoodArea);
    void    setStandNumber_Mall(int num);

    bool    outdoor_Market() const;
    bool    foodArea_Market() const;
    int     standNumber_Market() const;
    void    setOutdoor_Market(bool outdoor);
    void    setFoodArea_Market(bool hasFoodArea);
    void    setStandNumber_Market(int num);

    // ------ Orari di apertura ---------------------------------
    struct DayHours {
        QTime open;
        QTime close;
        bool  alwaysOpen  = false;
        bool  alwaysClosed= false;
    };
    DayHours hours(Weekday day) const; // 1=lunedì … 7=domenica
    void     setHours(Weekday day, const DayHours &hours);
    int getTypeIndex() const;
    void setEditing(bool enabled);
    bool isEditing() const;
    void resetFields();
    void showDetailPage(int index);

private:
    bool m_editing { false };
    Ui::CreatePlaceWidget *ui { nullptr };
    PlaceController *controller { nullptr };
};

#endif // CREATEPLACEWIDGET_H
