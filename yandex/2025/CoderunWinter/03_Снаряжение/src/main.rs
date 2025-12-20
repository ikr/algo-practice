use std::io::{stdin, stdout, BufWriter, Write};

pub mod mod_int {
    type ModInternalNum = i64;
    thread_local!(
        static MOD: std::cell::RefCell<ModInternalNum> = const { std::cell::RefCell::new(0) };
    );

    pub fn set_mod_int<T: ToInternalNum>(v: T) {
        MOD.with(|x| x.replace(v.to_internal_num()));
    }
    fn modulo() -> ModInternalNum {
        MOD.with(|x| *x.borrow())
    }

    #[derive(Debug)]
    pub struct ModInt(ModInternalNum);
    impl Clone for ModInt {
        fn clone(&self) -> Self {
            *self
        }
    }
    impl Copy for ModInt {}

    impl ModInt {
        fn internal_new(mut v: ModInternalNum) -> Self {
            let m = modulo();
            if v >= m {
                v %= m;
            }
            Self(v)
        }

        pub fn internal_pow(&self, mut e: ModInternalNum) -> Self {
            let mut result = 1;
            let mut cur = self.0;
            let modulo = modulo();
            while e > 0 {
                if e & 1 == 1 {
                    result *= cur;
                    result %= modulo;
                }
                e >>= 1;
                cur = (cur * cur) % modulo;
            }
            Self(result)
        }

        pub fn pow<T>(&self, e: T) -> Self
        where
            T: ToInternalNum,
        {
            self.internal_pow(e.to_internal_num())
        }

        pub fn value(&self) -> ModInternalNum {
            self.0
        }
    }

    pub trait ToInternalNum {
        fn to_internal_num(&self) -> ModInternalNum;
    }
    impl ToInternalNum for ModInt {
        fn to_internal_num(&self) -> ModInternalNum {
            self.0
        }
    }
    macro_rules! impl_primitive {
        ($primitive:ident) => {
            impl From<$primitive> for ModInt {
                fn from(v: $primitive) -> Self {
                    let v = v as ModInternalNum;
                    Self::internal_new(v)
                }
            }
            impl ToInternalNum for $primitive {
                fn to_internal_num(&self) -> ModInternalNum {
                    *self as ModInternalNum
                }
            }
        };
    }
    impl_primitive!(u8);
    impl_primitive!(u16);
    impl_primitive!(u32);
    impl_primitive!(u64);
    impl_primitive!(usize);
    impl_primitive!(i8);
    impl_primitive!(i16);
    impl_primitive!(i32);
    impl_primitive!(i64);
    impl_primitive!(isize);

    impl<T: ToInternalNum> std::ops::AddAssign<T> for ModInt {
        fn add_assign(&mut self, rhs: T) {
            let mut rhs = rhs.to_internal_num();
            let m = modulo();
            if rhs >= m {
                rhs %= m;
            }

            self.0 += rhs;
            if self.0 >= m {
                self.0 -= m;
            }
        }
    }

    impl<T: ToInternalNum> std::ops::Add<T> for ModInt {
        type Output = ModInt;
        fn add(self, rhs: T) -> Self::Output {
            let mut res = self;
            res += rhs;
            res
        }
    }
    impl<T: ToInternalNum> std::ops::SubAssign<T> for ModInt {
        fn sub_assign(&mut self, rhs: T) {
            let mut rhs = rhs.to_internal_num();
            let m = modulo();
            if rhs >= m {
                rhs %= m;
            }
            if rhs > 0 {
                self.0 += m - rhs;
            }
            if self.0 >= m {
                self.0 -= m;
            }
        }
    }
    impl<T: ToInternalNum> std::ops::Sub<T> for ModInt {
        type Output = Self;
        fn sub(self, rhs: T) -> Self::Output {
            let mut res = self;
            res -= rhs;
            res
        }
    }
    impl<T: ToInternalNum> std::ops::MulAssign<T> for ModInt {
        fn mul_assign(&mut self, rhs: T) {
            let mut rhs = rhs.to_internal_num();
            let m = modulo();
            if rhs >= m {
                rhs %= m;
            }
            self.0 *= rhs;
            self.0 %= m;
        }
    }
    impl<T: ToInternalNum> std::ops::Mul<T> for ModInt {
        type Output = Self;
        fn mul(self, rhs: T) -> Self::Output {
            let mut res = self;
            res *= rhs;
            res
        }
    }

    impl<T: ToInternalNum> std::ops::DivAssign<T> for ModInt {
        fn div_assign(&mut self, rhs: T) {
            let mut rhs = rhs.to_internal_num();
            let m = modulo();
            if rhs >= m {
                rhs %= m;
            }
            let inv = Self(rhs).internal_pow(m - 2);
            self.0 *= inv.value();
            self.0 %= m;
        }
    }

    impl<T: ToInternalNum> std::ops::Div<T> for ModInt {
        type Output = Self;
        fn div(self, rhs: T) -> Self::Output {
            let mut res = self;
            res /= rhs;
            res
        }
    }
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }

    fn next_n<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        let mut result: Vec<T> = Vec::with_capacity(n);
        for _ in 0..n {
            result.push(self.next());
        }
        result
    }
}

fn flaws_sum(m: i64, xs: Vec<i64>) -> i64 {
    type Mint = mod_int::ModInt;
    let total: Mint = xs.iter().fold(Mint::from(0), |acc, &x| acc + Mint::from(x));

    xs.into_iter()
        .map(|x| {
            let d = (total * x) / Mint::from(m);
            (Mint::from(x) - d).pow(2)
        })
        .fold(Mint::from(0), |acc, a| acc + Mint::from(a))
        .value()
}

fn main() {
    mod_int::set_mod_int(1_000_000_007);
    let stdout = stdout();
    let handle = stdout.lock();
    let mut writer = BufWriter::new(handle);

    let mut scanner = Scanner::default();
    let m: i64 = scanner.next();
    let n: usize = scanner.next();
    let xs: Vec<i64> = scanner.next_n(n);
    eprintln!("{:?}", xs);

    let result = flaws_sum(m, xs);
    writeln!(writer, "{result}").unwrap();

    writer.flush().unwrap();
}
