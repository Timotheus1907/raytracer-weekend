#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

#include "hittable.h"

class material {
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
		return false;
	}
};

class lambertian : public material {
public:
	lambertian(const color& albedo) : albedo(albedo) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scatter_direction = rec.normal + random_unit_vector();

		// Incase rec.normal and random_unit_vector() evaluate to zero
		if (scatter_direction.near_zero()) scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};

class metal : public material {
public:
	metal(const color& albedo) : albedo(albedo) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
		const override {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = ray(rec.t, reflected);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};

#endif