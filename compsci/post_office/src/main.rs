struct Postage {
    length: f32,
    height: f32,
    thickness: f32,
    weight: f32,
}

enum PostageClass {
    RegularPostcard,
    LargePostcard,
    Envelope,
    LargeEnvelope,
    Package,
    LargePackage,
    Unmailable,
}

impl Postage {
    pub fn class(&self) -> PostageClass {
        todo!()
    }
}

fn main() {
    println!("Hello, world!");
}
