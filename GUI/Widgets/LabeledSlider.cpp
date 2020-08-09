#include <iostream>

#include "LabeledSlider.h"

LabeledSlider::LabeledSlider(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
  
  //this->txtMin->setText(QString::number(this->horizontalSlider->minimum()));
  //this->txtMax->setText(QString::number(this->horizontalSlider->maximum()));

  this->horizontalSlider->setMinimum(this->txtMin->text().toInt());
  this->horizontalSlider->setMaximum(this->txtMax->text().toInt());

  this->lblCurrent->setText(QString::number(this->horizontalSlider->value()));

  this->Validator = new QIntValidator(0, 10000, this);
  this->txtMin->setValidator(this->Validator);
  this->txtMax->setValidator(this->Validator);
  
  connect(this->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slot_horizontalSlider_valueChanged(int)));
}

unsigned int LabeledSlider::value()
{
  return this->horizontalSlider->value();
}

void LabeledSlider::on_txtMin_textEdited( const QString & text )
{
  this->horizontalSlider-