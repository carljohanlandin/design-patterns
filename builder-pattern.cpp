#include <iostream>
#include <stdint.h>

// Using the Builder pattern makes sense only when your products
// are quite complex and require extensive configuration. The
// following two products are related, although they don't have
// a common interface.

// A car can have a GPS, trip computer and some number of
// seats. Different models of cars (sports car, SUV,
// cabriolet) might have different features installed or
// enabled.
class Car {
public:
	Car() = default;

	void setSeats(uint8_t seats)
	{
		this->seats = seats;
	}

	void setEngine(bool hasEngine)
	{
		this->engine = hasEngine;
	}

	void setGPS(bool hasGPS)
	{
		this->gps = hasGPS;
	}

	void setTripComputer(bool hasTripComputer)
	{
		this->tripComputer = hasTripComputer;
	}

private:
	bool engine;
	bool gps;
	bool tripComputer;
	uint8_t seats;
};

// Each car should have a user manual that corresponds to
// the car's configuration and describes all its features.
class Manual : public Car {
public:
	Manual() = default;


// private:
// 	bool engine;
// 	bool gps;
// 	bool tripComputer;
// 	uint8_t seats;
};

// The builder interface specifies methods for creating the
// different parts of the product objects.
class IBuilder {
public:
	virtual void reset() = 0;
	virtual void setSeats(uint8_t seats) = 0;
	virtual void setEngine(bool hasEngine) = 0;
	virtual void setTripComputer(bool hasTripComputer) = 0;
	virtual void setGPS(bool hasGPS) = 0;
};

// The concrete builder classes follow the builder interface and
// provide specific implementations of the building steps. Your
// program may have several variations of builders, each
// implemented differently.
class CarBuilder : public IBuilder {
private:
	Car* car;

public:
	CarBuilder()
	{
		this->reset();
	}

	void reset() override
	{
		this->car = new Car();
	}

	void setSeats(uint8_t seats) override
	{
		car->setSeats(seats);
	}

	void setEngine(bool hasEngine) override
	{
		car->setEngine(hasEngine);
	}

	void setTripComputer(bool hasTripComputer) override
	{
		car->setTripComputer(hasTripComputer);
	}

	void setGPS(bool hasGPS) override
	{
		car->setGPS(hasGPS);
	}

	// Concrete builders are supposed to provide their own
	// methods for retrieving results. That's because various
	// types of builders may create entirely different products
	// that don't all follow the same interface. Therefore such
	// methods can't be declared in the builder interface (at
	// least not in a statically-typed programming language).
	//
	// Usually, after returning the end result to the client, a
	// builder instance is expected to be ready to start
	// producing another product. That's why it's a usual
	// practice to call the reset method at the end of the
	// `getProduct` method body. However, this behavior isn't
	// mandatory, and you can make your builder wait for an
	// explicit reset call from the client code before disposing
	// of the previous result.
	Car getProduct()
	{
		Car product = *this->car;
		this->reset();
		return product;
	}

};

// Unlike other creational patterns, builder lets you construct
// products that don't follow the common interface.
class CarManualBuilder : public IBuilder {
public:
	CarManualBuilder()
	{
		this->reset();
	}

	void reset() override
	{
		this->manual = new Manual();
	}

	void setSeats(uint8_t seats) override
	{
		this->manual->setSeats(seats);
	}

	void setEngine(bool hasEngine) override
	{
		this->manual->setEngine(hasEngine);
	}

	void setTripComputer(bool hasTripComputer) override
	{
		this->manual->setTripComputer(hasTripComputer);
	}

	void setGPS(bool hasGPS) override
	{
		this->manual->setGPS(hasGPS);
	}

	Manual getProduct()
	{
		Manual product = *this->manual;
		this->reset();
		return product;
	}

private:
	Manual* manual;
};


// The director is only responsible for executing the building
// steps in a particular sequence. It's helpful when producing
// products according to a specific order or configuration.
// Strictly speaking, the director class is optional, since the
// client can control builders directly.
class Director {
private:
	IBuilder* builder;

public:
	// The director works with any builder instance that the
	// client code passes to it. This way, the client code may
	// alter the final type of the newly assembled product.
	void setBuilder(IBuilder* builder)
	{
		this->builder = builder;
	}

	// The director can construct several product variations
	// using the same building steps.
	void constructSportsCar(IBuilder* builder)
	{
		builder->reset();
		builder->setSeats(2);
		builder->setEngine(true);
		builder->setTripComputer(true);
		builder->setGPS(false);

		std::cout << "Sports Car constructed\n";
	}

	void constructSUV(IBuilder* builder)
	{
		builder->reset();
		builder->setSeats(5);
		builder->setEngine(false);
		builder->setTripComputer(false);
		builder->setGPS(true);

		std::cout << "SUV car constructed\n";
	}
};

// The client code creates a builder object, passes it to the
// director and then initiates the construction process. The end
// result is retrieved from the builder object.
class Application {
public:
	void makeCar()
	{
		Director* director = new Director();

		CarBuilder* builder = new CarBuilder();
		director->constructSportsCar(builder);
		Car car = builder->getProduct();

		CarManualBuilder* manBuilder = new CarManualBuilder();
		director->constructSportsCar(manBuilder);

		// The final product is often retrieved from a builder
		// object since the director isn't aware of and not
		// dependent on concrete builders and products.
		Manual manual = manBuilder->getProduct();
	}
};

int main(int argc, char const *argv[])
{
	Application app;

	app.makeCar();
	return 0;
}


