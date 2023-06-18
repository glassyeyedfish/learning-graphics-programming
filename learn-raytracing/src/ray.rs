use glam::Vec3;

pub struct Ray {
    // oridin
    pub o: Vec3,
    // direction
    pub d: Vec3,
}

impl Ray {
    pub fn new(o: Vec3, d: Vec3) -> Self {
        Self { o, d }
    }

    pub fn at(&self, t: f32) -> Vec3 {
        self.o + (t * self.d)
    }
}
