#include "radiopropa/Candidate.h"
#include "radiopropa/ParticleID.h"
#include "radiopropa/module/SimplePropagation.h"
#include "radiopropa/module/PropagationCK.h"

#include "gtest/gtest.h"

namespace radiopropa {

TEST(testSimplePropagation, step) {
	double minStep = 20;
	double maxStep = 100;
	SimplePropagation propa(minStep, maxStep);

	ParticleState p;
	p.setPosition(Vector3d(0, 0, 0));
	p.setDirection(Vector3d(0, 1, 0));

	Candidate c(p);
	c.setNextStep(10);

	propa.process(&c);

	EXPECT_EQ(minStep, c.getCurrentStep());
	EXPECT_EQ(maxStep, c.getNextStep());
	EXPECT_EQ(Vector3d(0,  0, 0), c.created.getPosition());
	EXPECT_EQ(Vector3d(0,  1, 0), c.created.getDirection());
	EXPECT_EQ(Vector3d(0,  0, 0), c.previous.getPosition());
	EXPECT_EQ(Vector3d(0,  1, 0), c.previous.getDirection());
	EXPECT_EQ(Vector3d(0, 20, 0), c.current.getPosition());
	EXPECT_EQ(Vector3d(0,  1, 0), c.current.getDirection());
}


TEST(testPropagationCK, zeroField) {
	PropagationCK propa(new UniformMagneticField(Vector3d(0, 0, 0)));

	double minStep = 0.1 * kpc;
	propa.setMinimumStep(minStep);

	ParticleState p;
	p.setId(nucleusId(1, 1));
	p.setFrequency(100 * EeV);
	p.setPosition(Vector3d(0, 0, 0));
	p.setDirection(Vector3d(0, 1, 0));
	Candidate c(p);
	c.setNextStep(0);

	propa.process(&c);

	EXPECT_DOUBLE_EQ(minStep, c.getCurrentStep());  // perform minimum step
	EXPECT_DOUBLE_EQ(5 * minStep, c.getNextStep());  // acceleration by factor 5
}

TEST(testPropagationCK, proton) {
	PropagationCK propa(new UniformMagneticField(Vector3d(0, 0, 1 * nG)));

	double minStep = 0.1 * kpc;
	propa.setMinimumStep(minStep);

	ParticleState p;
	p.setId(nucleusId(1, 1));
	p.setFrequency(100 * EeV);
	p.setPosition(Vector3d(0, 0, 0));
	p.setDirection(Vector3d(0, 1, 0));
	Candidate c(p);
	c.setNextStep(0);

	propa.process(&c);

	EXPECT_DOUBLE_EQ(minStep, c.getCurrentStep());  // perform minimum step
	EXPECT_DOUBLE_EQ(5 * minStep, c.getNextStep());  // acceleration by factor 5
}

TEST(testPropagationCK, neutron) {
	PropagationCK propa(new UniformMagneticField(Vector3d(0, 0, 1 * nG)));
	propa.setMinimumStep(1 * kpc);
	propa.setMaximumStep(42 * Mpc);

	ParticleState p;
	p.setId(nucleusId(1, 0));
	p.setFrequency(100 * EeV);
	p.setPosition(Vector3d(0, 0, 0));
	p.setDirection(Vector3d(0, 1, 0));
	Candidate c(p);

	propa.process(&c);

	EXPECT_DOUBLE_EQ(1 * kpc, c.getCurrentStep());
	EXPECT_DOUBLE_EQ(42 * Mpc, c.getNextStep());
	EXPECT_EQ(Vector3d(0, 1 * kpc, 0), c.current.getPosition());
	EXPECT_EQ(Vector3d(0, 1, 0), c.current.getDirection());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

} // namespace radiopropa
