#ifndef FloatSlider_H
#define FloatSlider_H

#include <QtDesigner/QDesignerExportWidget>
class QDoubleValidator;

#include "LabeledSlider.h"

// This slider should always be set from min = 0 to max = 100.
// This then lets us interpret the difference between the min and max
// as a percentage.
class QDESIGNER_WIDGET_EXPORT FloatSlider : p