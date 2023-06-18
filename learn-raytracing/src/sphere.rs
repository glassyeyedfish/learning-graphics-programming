use glam::Vec3;

use crate::ray::Ray;

pub struct Sphere {
    // center point
    pub c: Vec3,
    // radius        let color_white = Vec3::ONE;
    pub r: f32,
}

impl Sphere {
    pub fn new(c: Vec3, r: f32) -> Self {
        Self { c, r }
    }

    pub fn is_hit_at(&self, r: &Ray) -> f32 {
        let oc = r.o - self.c;
        let a = r.d.dot(r.d);
        let hb = oc.dot(r.d);
        let c = oc.dot(oc) - self.r * self.r;
        let descriminant =  hb*hb - a*c;

        if descriminant < 0.0 {
            return -1.0;
        } else {
            return (-hb - descriminant.sqrt()) / a;
        }
    }
}