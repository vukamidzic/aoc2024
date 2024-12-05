use std::{
    collections::HashMap, 
    fs::File, 
    io::{BufRead, BufReader},
    cmp::Ordering
};

fn check_update_rules(update: &Vec<i32>, rules: &HashMap<i32, Vec<i32>>) -> bool {
    for i in 0..update.len()-1 {
        match rules.contains_key(&update[i]) {
            true => {
                let not_in_rule: &Vec<_> = &update[i+1..]
                    .iter()
                    .filter(|x| !rules.get(&update[i]).unwrap().contains(x))
                    .collect();

                if not_in_rule.iter().any(|x| rules.get(x).unwrap().contains(&update[i])) {
                    return false;
                }
            }
            _ => {
                let rest : &Vec<_> = &update[i+1..].iter().collect();

                if rest.iter().any(|x| rules.get(x).unwrap().contains(&update[i])) {
                    return false;
                }
            }
        } 
    }

    true
}

fn part1(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let reader: BufReader<_> = BufReader::new(input);
    let data: Vec<_> = reader.lines().map(|x| x.unwrap()).collect();

    let empty_row_idx = data.iter().position(|x| x.is_empty()).unwrap();

    let mut rules: HashMap<i32, Vec<i32>> = HashMap::new();
    for line in &data[..empty_row_idx] {
        let parts: Vec<_> = line.split("|").collect();
        let key: i32 = parts[0].parse().unwrap();
        let value: i32 = parts[1].parse().unwrap();

        rules.entry(key).or_insert(Vec::new()).push(value);
    }

    let mut updates: Vec<Vec<i32>> = Vec::new();
    for line in &data[empty_row_idx+1..] {
        updates.push(line.split(",").map(|c| c.parse().unwrap()).collect());
    }

    let mut res = 0;
    for update in updates {
        if check_update_rules(&update, &rules) {
            let middle_idx = (update.len()-1)/2;
            res += update[middle_idx];
        }
    }

    res
}

fn part2(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let reader: BufReader<_> = BufReader::new(input);
    let data: Vec<_> = reader.lines().map(|x| x.unwrap()).collect();

    let empty_row_idx = data.iter().position(|x| x.is_empty()).unwrap();

    let mut rules: HashMap<i32, Vec<i32>> = HashMap::new();
    for line in &data[..empty_row_idx] {
        let parts: Vec<_> = line.split("|").collect();
        let key: i32 = parts[0].parse().unwrap();
        let value: i32 = parts[1].parse().unwrap();

        rules.entry(key).or_insert(Vec::new()).push(value);
    }

    let mut updates: Vec<Vec<i32>> = Vec::new();
    for line in &data[empty_row_idx+1..] {
        updates.push(line.split(",").map(|c| c.parse().unwrap()).collect());
    }

    let mut res = 0;
    for mut update in updates {
        if !check_update_rules(&update, &rules) {
            update.sort_by(|a, b| {
                match rules.get(a) {
                    Some(v) => {
                        if v.contains(b) { Ordering::Less } else { Ordering::Greater }
                    },
                    _ => {Ordering::Greater}
                }
            });
    
            let middle_idx = (update.len()-1)/2;
            res += update[middle_idx];        
        }
    }

    res
}

fn main() {
    assert_eq!(part1("src/day5/test.txt"),143);
    println!("Part1 result: {}", part1("src/day5/input.txt"));

    assert_eq!(part2("src/day5/test.txt"),123);
    println!("Part2 result: {}", part2("src/day5/input.txt"));
}