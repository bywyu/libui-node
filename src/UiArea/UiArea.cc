#include "../../libui/ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"
#include "nbind/api.h"

INHERITS_CONTROL_METHODS(UiArea)
_UI_EXTERN void uiAreaSetSize(uiArea *a, int width, int height);
// TODO uiAreaQueueRedraw()
_UI_EXTERN void uiAreaQueueRedrawAll(uiArea *a);
_UI_EXTERN void uiAreaScrollTo(uiArea *a, double x, double y, double width, double height);

void UiArea::setSize(int width, int height) {
	uiAreaSetSize(
		(uiArea *) getHandle(),
		width,
		height
	);
}

void UiArea::queueRedrawAll() {
	uiAreaQueueRedrawAll(
		(uiArea *) getHandle()
	);
}

void UiArea::scrollTo(double x, double y, double width, double height) {
	uiAreaScrollTo(
		(uiArea *) getHandle(),
		x,
		y,
		width,
		height
	);
}

UiArea::UiArea(
	nbind::cbFunction &drawCb,
	nbind::cbFunction &mouseEventCb ,
	nbind::cbFunction &mouseCrossedCb,
	nbind::cbFunction &dragBrokenCb,
	nbind::cbFunction &keyEventCb
) : UiControl( (uiControl*) uiNewArea(
	(uiAreaHandler *) UiAreaHandlerFactory::build(
		drawCb,
		mouseEventCb,
		mouseCrossedCb,
		dragBrokenCb,
		keyEventCb
	)
)) {}

UiArea::UiArea(
	nbind::cbFunction &drawCb,
	nbind::cbFunction &mouseEventCb ,
	nbind::cbFunction &mouseCrossedCb,
	nbind::cbFunction &dragBrokenCb,
	nbind::cbFunction &keyEventCb,
	int width,
	int height
) : UiControl( (uiControl*) uiNewScrollingArea(
	(uiAreaHandler *) UiAreaHandlerFactory::build(
		drawCb,
		mouseEventCb,
		mouseCrossedCb,
		dragBrokenCb,
		keyEventCb
	),
	width,
	height
)) {}


NBIND_CLASS(UiArea) {
	construct<nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &>();
	construct<nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &, int, int>();
	DECLARE_CONTROL_METHODS()
	method(setSize);
	method(queueRedrawAll);
	method(scrollTo);
}