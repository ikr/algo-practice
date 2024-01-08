use std::collections::{HashMap, HashSet, VecDeque};

const INF: i32 = 1_000_000_000;

fn read_initial_grid_from_stdin() -> Vec<Vec<char>> {
    let mut result: Vec<Vec<char>> = Vec::new();
    loop {
        let mut line = String::new();
        let bytes_read = std::io::stdin().read_line(&mut line).unwrap();
        if bytes_read == 0 {
            break;
        }
        result.push(line.trim_end().chars().collect());
    }
    result
}

fn dbg_grid(grid: &Vec<Vec<char>>) -> () {
    for row in grid.iter() {
        for c in row.iter() {
            eprint!("{}", c);
        }
        eprintln!();
    }
}

fn grid_with_units_added(
    mut grid: Vec<Vec<char>>,
    unit_locs: Vec<Loc>,
    unit_symbol: char,
) -> Vec<Vec<char>> {
    for loc in unit_locs.iter() {
        grid[loc.ro as usize][loc.co as usize] = unit_symbol;
    }
    grid
}

fn depopulated_grid(grid: &Vec<Vec<char>>) -> Vec<Vec<char>> {
    let mut result: Vec<Vec<char>> = Vec::new();
    for row in grid.iter() {
        let mut new_row: Vec<char> = Vec::new();
        for c in row.iter() {
            match c {
                '#' | '.' => new_row.push(*c),
                _ => new_row.push('.'),
            }
        }
        result.push(new_row);
    }
    result
}

fn drop_from(vec: &mut Vec<Loc>, loc: &Loc) -> () {
    if let Some(i) = vec.iter().position(|x| x == loc) {
        vec.remove(i);
    }
}

#[derive(Eq, Hash, PartialEq, Clone, Debug)]
struct Loc {
    ro: usize,
    co: usize,
}

#[derive(Clone, Debug)]
struct Unit {
    hit_points: i32,
    attack_power: i32,
}

impl Unit {
    fn attacked(&self, other: &Unit) -> Option<Unit> {
        if other.hit_points <= self.attack_power {
            None
        } else {
            Some(Unit {
                hit_points: other.hit_points - self.attack_power,
                attack_power: other.attack_power,
            })
        }
    }
}

struct Squad {
    units: HashMap<Loc, Unit>,
    symbol: char,
}

impl Squad {
    fn in_grid(grid: &Vec<Vec<char>>, symbol: char) -> Squad {
        let mut units: HashMap<Loc, Unit> = HashMap::new();
        for (ro, row_vec) in grid.iter().enumerate() {
            for (co, cell) in row_vec.iter().enumerate() {
                if *cell == symbol {
                    units.insert(
                        Loc { ro, co },
                        Unit {
                            hit_points: 200,
                            attack_power: 3,
                        },
                    );
                }
            }
        }
        Squad { units, symbol }
    }
}

struct Dungeon {
    grid: Vec<Vec<char>>,
    squads: [Squad; 2],
}

impl Dungeon {
    fn play_round(&mut self) -> () {
        let mut q = self.all_unit_locations();
        q.sort_by_key(|loc| (-(loc.ro as i32), -(loc.co as i32)));

        while !q.is_empty() {
            let unit_loc = q.pop().unwrap();

            match self.target_for_an_attack(&unit_loc) {
                Some(target_loc) => {
                    self.attack_with_unit(&unit_loc, &target_loc);
                    if !self.is_a_unit(&target_loc) {
                        drop_from(&mut q, &target_loc);
                    }
                }
                None => {
                    if let Some(unit_loc_) = self.move_unit(&unit_loc) {
                        if let Some(target_loc) = self.target_for_an_attack(&unit_loc_) {
                            self.attack_with_unit(&unit_loc_, &target_loc);
                            if !self.is_a_unit(&target_loc) {
                                drop_from(&mut q, &target_loc);
                            }
                        }
                    }
                }
            }
        }
    }

    fn target_for_an_attack(&self, unit_loc: &Loc) -> Option<Loc> {
        let own_squad_index = self.squad_index(&unit_loc);
        let other_squad_index = 1 - own_squad_index;
        let enemy_symbol = self.squads[other_squad_index].symbol;

        let mut alts = self.adjacent_of_kind(&unit_loc, enemy_symbol);
        alts.sort_by_key(|loc| {
            self.squads[other_squad_index]
                .units
                .get(loc)
                .unwrap()
                .hit_points
        });
        alts.first().cloned()
    }

    fn attack_with_unit(&mut self, unit_loc: &Loc, target_loc: &Loc) -> () {
        let attacker_squad_index = self.squad_index(unit_loc);
        let defender_squad_index = self.squad_index(target_loc);
        assert!(attacker_squad_index != defender_squad_index);

        let attacker = self.squads[attacker_squad_index]
            .units
            .get(unit_loc)
            .unwrap()
            .clone();

        let defender = self.squads[defender_squad_index]
            .units
            .get(target_loc)
            .unwrap()
            .clone();

        self.squads[defender_squad_index].units.remove(target_loc);

        if let Some(defender_) = attacker.attacked(&defender) {
            self.squads[defender_squad_index]
                .units
                .insert(target_loc.clone(), defender_);
        }
    }

    fn move_unit(&mut self, loc: &Loc) -> Option<Loc> {
        let own_squad_index = self.squad_index(&loc);
        let other_squad_index = 1 - own_squad_index;
        let unit = self.squads[own_squad_index].units.get(loc).unwrap().clone();

        let mut alts: HashSet<Loc> = HashSet::new();
        for u in self.squads[other_squad_index].units.keys() {
            for v in self.adjacent_of_kind(u, '.') {
                alts.insert(v);
            }
        }

        if !alts.is_empty() {
            let mut alts_vec: Vec<Loc> = alts.into_iter().collect();
            alts_vec.sort_by_key(|loc| (loc.ro, loc.co));
            let target = self.closest_of(loc, alts_vec);

            let own_range = self.adjacent_of_kind(loc, '.');
            if !own_range.is_empty() {
                let next_step_loc = self.closest_of(&target, own_range);
                self.squads[own_squad_index].units.remove(loc);
                self.squads[own_squad_index]
                    .units
                    .insert(next_step_loc.clone(), unit);
                Some(next_step_loc)
            } else {
                None
            }
        } else {
            None
        }
    }

    fn all_unit_locations(&self) -> Vec<Loc> {
        let mut result: Vec<Loc> = Vec::new();
        for squad in self.squads.iter() {
            result.extend(squad.units.keys().cloned());
        }
        result
    }

    fn is_a_unit(&self, loc: &Loc) -> bool {
        self.squads[0].units.contains_key(&loc) || self.squads[1].units.contains_key(&loc)
    }

    fn is_game_over(&self) -> bool {
        self.squads[0].units.is_empty() || self.squads[1].units.is_empty()
    }

    fn total_health_points_remaining(&self) -> i32 {
        let mut result = 0;
        for squad in self.squads.iter() {
            for unit in squad.units.values() {
                result += unit.hit_points;
            }
        }
        result
    }

    fn squad_index(&self, loc: &Loc) -> usize {
        for (i, squad) in self.squads.iter().enumerate() {
            if squad.units.contains_key(loc) {
                return i;
            }
        }
        panic!("No squad unit at location {:?}", loc);
    }

    fn closest_of(&self, src: &Loc, mut dest: Vec<Loc>) -> Loc {
        let h = self.grid.len();
        assert!(h > 0);
        let w = self.grid[0].len();
        let mut distance: Vec<Vec<i32>> = vec![vec![INF; w]; h];
        distance[src.ro][src.co] = 0;

        let mut q: VecDeque<Loc> = VecDeque::new();
        q.push_back(src.clone());

        while !q.is_empty() {
            let u = q.pop_front().unwrap();
            for v in self.adjacent_of_kind(&u, '.') {
                if distance[v.ro][v.co] != INF {
                    continue;
                }
                distance[v.ro][v.co] = distance[u.ro][u.co] + 1;
                q.push_back(v);
            }
        }

        assert!(!dest.is_empty());
        dest.sort_by_key(|loc| distance[loc.ro][loc.co]);
        dest[0].clone()
    }

    fn adjacent_of_kind(&self, loc: &Loc, kind: char) -> Vec<Loc> {
        let mut result: Vec<Loc> = Vec::new();
        for (ro, co) in [
            (loc.ro - 1, loc.co),
            (loc.ro, loc.co - 1),
            (loc.ro, loc.co + 1),
            (loc.ro + 1, loc.co),
        ] {
            if self.cell_at(&Loc { ro, co }) == kind {
                result.push(Loc { ro, co });
            }
        }
        result
    }

    fn cell_at(&self, loc: &Loc) -> char {
        for squad in self.squads.iter() {
            if squad.units.contains_key(loc) {
                return squad.symbol;
            }
        }
        self.grid[loc.ro][loc.co]
    }

    fn dbg(&self) -> () {
        let mut grid = self.grid.clone();
        for squad in self.squads.iter() {
            let locatoins: Vec<Loc> = squad.units.keys().cloned().collect();
            grid = grid_with_units_added(grid, locatoins, squad.symbol);
        }
        dbg_grid(&grid);
        eprintln!("{:?}", self.squads[0].units);
        eprintln!("{:?}", self.squads[1].units);
    }
}

fn main() {
    let grid = read_initial_grid_from_stdin();
    let elves = Squad::in_grid(&grid, 'E');
    let goblins = Squad::in_grid(&grid, 'G');
    let mut dungeon = Dungeon {
        grid: depopulated_grid(&grid),
        squads: [elves, goblins],
    };

    for i in 1..=10_000 {
        dungeon.play_round();
        dungeon.dbg();
        eprintln!();

        if dungeon.is_game_over() {
            println!("{}", i * dungeon.total_health_points_remaining());
            break;
        }
    }
}
