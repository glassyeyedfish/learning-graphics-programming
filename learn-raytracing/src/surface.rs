use glam::Vec3;
use image::{ImageBuffer, RgbImage};

pub struct Surface {
    img: RgbImage,
}

impl Surface {
    pub fn new(width: u32, height: u32) -> Self {
        Self {
            img: ImageBuffer::new(width, height),
        }
    }

    pub fn put(&mut self, x: u32, y: u32, color: Vec3) {
        self.img.put_pixel(
            x,
            y,
            image::Rgb([
                (color.x.clamp(0.0, 1.0) * 256.0) as u8,
                (color.y.clamp(0.0, 1.0) * 256.0) as u8,
                (color.z.clamp(0.0, 1.0) * 256.0) as u8,
            ]),
        )
    }

    pub fn export(&self) {
        self.img.save("test.png").unwrap();
    }
}
