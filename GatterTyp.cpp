#include "GatterTyp.h"


GatterTyp::GatterTyp()
{
    //ctor
}

GatterTyp::~GatterTyp()
{
    //dtor
}

void GatterTyp::setName(string n)
{
    name=n;

}

string GatterTyp::getName(void)
{
    return name;
}

double GatterTyp::getGrundLaufzeit(void)
{
    return grundLaufzeit;
}

short GatterTyp::getLastFaktor(void)
{
    return lastFaktor;
}

short GatterTyp::getLastKapazitaet(void)
{
    return lastKapazitaet;
}

short GatterTyp::getEingaenge(void)
{
    return eingaenge;
}

bool GatterTyp::getIsFlipflop(void)
{
    return false;
}


void GatterTyp::setGrundLaufzeit(double gl)
{
    grundLaufzeit =gl;
}

void GatterTyp::setLastFaktor(short lf)
{
    lastFaktor= lf;
}

void GatterTyp::setLastKapazitaet(short lk)
{
    lastKapazitaet=lk;
}

void GatterTyp::setEingaenge(short ei)
{
    eingaenge=ei;
}
