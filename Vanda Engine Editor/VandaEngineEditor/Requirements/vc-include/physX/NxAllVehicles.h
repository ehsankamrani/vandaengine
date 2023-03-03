#ifndef NX_ALL_VEHICLES
#define NX_ALL_VEHICLES

#include <set>
#include "NxVehicle.h"

class NxAllVehicles {
private:
	static std::set<NxVehicle*> _allVehicles;
	static NxArray<NxVehicle*> _allVehiclesSequential;
	static std::set<NxVehicle*> _allChildVehicles;
	
	static NxI32 _activeVehicle;
	static NxVehicle* _activeVehicleP;
	static void setActiveVehicleP();
public:
	static void AddVehicle(NxVehicle* v);
	static void AddChildVehicle(NxVehicle* v);
	//static void RemoveVehicle(NxVehicle* v);

	static void updateAllVehicles(NxReal lastTimeStep);
	static void drawVehicles(bool debug = false);

	static bool isVehicle(NxVehicle* v);
	static void handlePair(NxContactPair& pair, NxU32 events);

	static NxU32 getNumberOfVehicles() { return (NxU32)_allVehicles.size(); }
	static void setActiveVehicle(NxI32 v) { _activeVehicle = v; setActiveVehicleP(); }
	static NxVehicle* getActiveVehicle() { return _activeVehicleP; }
	static NxI32 getActiveVehicleNumber() { return _activeVehicle; }
	static void selectNext();

};

#endif
