#include "../Headers/Bridge.h"
#include "../Headers/Observer.h"

Bridge::Bridge(Observer* _observer) : observer(_observer) {}

void Bridge::transUpdate(Publisher* subject, std::string message) {

	observer->update(subject, message);
}