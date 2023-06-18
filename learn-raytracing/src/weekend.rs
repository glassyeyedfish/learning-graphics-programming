use std::f32::INFINITY;

use glam::Vec3;

use rand::prelude::*;

use crate::ray::Ray;
use crate::sphere::Sphere;

pub struct Weekend {
    pub aspect_ratio: f32,
    pub img_width: u32,
    pub img_height: u32,
    pub view_width: f32,
    pub view_height: f32,
    pub focal_length: f32,

    pub spheres: Vec<Sphere>,

    pub rand_rng: ThreadRng,
}

impl Weekend {
    pub fn new(aspect_ratio: f32, img_width: u32, view_width: f32, focal_length: f32) -> Self {
        let img_height = (img_width as f32 / aspect_ratio) as u32;
        let view_height = 2.0 / aspect_ratio;
        let spheres = Vec::new();
        let rand_rng = thread_rng();

        Self {
            aspect_ratio,
            img_width,
            img_height,
            view_width,
            view_height,
            focal_length,
            spheres,
            rand_rng,
        }
    }

    pub fn img_to_view_sample(&mut self, x: u32, y: u32) -> Vec3 {
        let x = x as f32 + self.rand_rng.gen_range(0.0..1.0);
        let y = y as f32 + self.rand_rng.gen_range(0.0..1.0);
        Vec3::new(
            x * (self.view_width / self.img_width as f32) - (self.view_width / 2.0),
            y * (self.view_height / self.img_height as f32) - (self.view_height / 2.0),
            self.focal_length,
        )
    }

    pub fn ray_color_sample(&mut self, x: u32, y: u32) -> Vec3 {
        // Create ray to trace (with some randomization)
        let d = self.img_to_view_sample(x, y);
        let r = Ray::new(Vec3::ZERO, d);

        // Get the color of the sphere
        let mut min_t = INFINITY;
        let mut hit_sphere = None;
        for sphere in &self.spheres {
            let t = sphere.is_hit_at(&r);
            if t < min_t && t > 0.0 {
                min_t = t;
                hit_sphere = Some(sphere);
            }
        }

        match hit_sphere {
            Some(sphere) => {
                // Normal color
                let n = r.at(min_t) - sphere.c;
                let n = n * n.length_recip();
                return 0.5 * (n + Vec3::ONE);
            },
            None => {
                // Default color (sky gradient)
                let s = (d.y + self.view_height / 2.0) / self.view_height;
                return Vec3::new(0.5, 0.7, 1.0).lerp(Vec3::ONE, s);
            }
        }
    }
}
