#include "capturearea.h"
#include "settings.h"
#include "task.h"

CaptureArea::CaptureArea(const QRect &rect, const Settings &settings)
  : rect_(rect)
  , doTranslation_(settings.doTranslation)
  , sourceLanguage_(settings.sourceLanguage)
  , targetLanguage_(settings.targetLanguage)
  , translators_(settings.translators)
{
}

TaskPtr CaptureArea::task(const QPixmap &pixmap) const
{
  if (pixmap.isNull() || rect_.width() < 3 || rect_.height() < 3)
    return {};

  auto task = std::make_shared<Task>();
  task->captured = pixmap.copy(rect_);
  task->capturePoint = rect_.topLeft();
  task->sourceLanguage = sourceLanguage_;
  if (doTranslation_ && !translators_.isEmpty()) {
    task->targetLanguage = targetLanguage_;
    task->translators = translators_;
  }

  return task;
}