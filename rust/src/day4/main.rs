use std::{fs::File, io::{BufReader, BufRead}};

fn check_substr(curr: (i32,i32), grid: &Vec<Vec<char>>, dir: &(i32, i32)) -> bool {
    let (y, x) = curr;
    let target: String = "XMAS".to_string();

    for i in 0..target.len() {
        let new_y = y + (i as i32)*dir.0;
        let new_x = x + (i as i32)*dir.1;

        if new_y >= (grid.len() as i32) || new_x >= (grid[0].len() as i32) ||
        new_y < 0 || new_x < 0 || grid[new_y as usize][new_x as usize] != target.chars().nth(i).unwrap() {
            return false;
        }
    }

    true
}

fn part1(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let mut data: Vec<Vec<char>> = vec![];
    let reader : BufReader<_> = BufReader::new(input);

    for line in reader.lines() {
        match line {
            Ok(content) => data.push(content.chars().collect()),
            Err(_) => {}
        }
    }

    let dirs: Vec<(i32,i32)> = vec![
        (0,1), 
        (1,0), 
        (-1,0), 
        (0,-1), 
        (1,1),
        (-1,-1),
        (1,-1),
        (-1,1)
    ];
    let mut res = 0;
    for i in 0..data.len() {
        for j in 0..data[0].len() {
            for dir in &dirs {
                if check_substr((i as i32,j as i32), &data, dir) {
                    res += 1;
                }
            }
        }
    }

    res
}

fn in_bounds(x: i32, y: i32, n: i32, m: i32) -> bool {
    x-1 >= 0 && y-1 >= 0 && x+1 < n && y+1 < m
}

fn check_diagonal_neighs(up_left: char, up_right: char, down_left: char, down_right: char) -> bool {
    vec![up_left,up_right,down_left,down_right]
        .iter()
        .all(|&x| x == 'M' || x == 'S') && 
        up_left != down_right &&
        up_right != down_left
}

fn part2(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let mut data: Vec<Vec<char>> = vec![];
    let reader : BufReader<_> = BufReader::new(input);

    for line in reader.lines() {
        match line {
            Ok(content) => data.push(content.chars().collect()),
            Err(_) => {}
        }
    }

    let mut res = 0;

    for i in 0..data.len() {
        for j in 0..data[0].len() {
            let (x,y): (i32,i32) = (i as i32,j as i32);
            let (n,m): (i32,i32) = (data.len() as i32,data[0].len() as i32);

            if in_bounds(x,y,n,m) && data[i][j] == 'A' {
                let up_left = data[i-1][j-1];
                let up_right = data[i-1][j+1];
                let down_left = data[i+1][j-1];
                let down_right = data[i+1][j+1];

                if check_diagonal_neighs(up_left, up_right, down_left, down_right) {
                    res += 1;
                }
            }
        }
    }

    res
}

fn main() {
    assert_eq!(part1("src/day4/test.txt"), 18);
    println!("Part1 result: {}", part1("src/day4/input.txt"));

    assert_eq!(part2("src/day4/test.txt"), 9);
    println!("Part2 result: {}", part2("src/day4/input.txt"));
}
