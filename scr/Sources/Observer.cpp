#include "../Headers/Observer.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

// Title's observer description //

TileObs::TileObs(std::string fname) {

	file.open(fname);
}

TileObs::~TileObs() {

	if (file.is_open()) file.close();
}

void TileObs::update(Publisher* subject, std::string message) {

	if (file.is_open()) file << dynamic_cast<Tile*>(subject) << ' ' << message << '\n';
}