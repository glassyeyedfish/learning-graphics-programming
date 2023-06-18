use glam::Vec3;

use crate::sphere::Sphere;
use crate::surface::Surface;
use crate::weekend::Weekend;

mod ray;
mod sphere;
mod surface;
mod weekend;

fn main() {
    // Constants for Main Function
    let sample_count = 8;

    // Constants for Weekend
    let aspect_ratio = 4.0 / 3.0;
    let img_width = 640;
    let view_width = 2.0;
    let focal_length = 1.0;

    let mut weekend = Weekend::new(aspect_ratio, img_width, view_width, focal_length);
    let mut surface = Surface::new(weekend.img_width, weekend.img_height);

    weekend.spheres.push(Sphere::new(Vec3::new(0.5, 0.0, 2.0), 1.0));
    weekend.spheres.push(Sphere::new(Vec3::new(-1.5, -0.5, 2.0), 0.5));
    weekend.spheres.push(Sphere::new(Vec3::new(0.0, 100.0, 50.0), 100.0));

    for x in 0..weekend.img_width {
        // Progress message
        let progress_current = x + 1;
        let progress_final = weekend.img_width;
        println!("Rendering: {progress_current} / {progress_final}");

        for y in 0..weekend.img_height {
            // Sample to get the color
            let mut color = weekend.ray_color_sample(x, y);
            for _i in 1..sample_count {
                color += weekend.ray_color_sample(x, y);
            }
            color /= sample_count as f32;

            // Trace each ray
            surface.put(x, y, color);
        }
    }

    surface.export();
}
