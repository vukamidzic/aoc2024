use std::{fs::File, io::{BufReader,BufRead}};
use std::collections::{VecDeque,HashSet};

fn can_visit(pos: &(i32,i32), grid: &Vec<Vec<u32>>, visited: &HashSet<(i32,i32)>) -> bool {
    pos.0 >= 0 && pos.1 >= 0 && 
    pos.0 < grid.len() as i32 && pos.1 < grid[0].len() as i32 && 
    !visited.contains(pos)
}

fn bfs(grid: &Vec<Vec<u32>>, src: (i32, i32)) -> i32 {
    let mut res = 0;
    let mut q: VecDeque<(i32,i32)> = VecDeque::new();
    let mut visited: HashSet<(i32,i32)> = HashSet::new();

    q.push_front(src);

    let dirs = [(0,1),(0,-1),(1,0),(-1,0)];
    while !q.is_empty() {
        let pos = q.pop_front().unwrap();

        if grid[pos.0 as usize][pos.1 as usize] == 9 {
            res += 1;
        }   
        else {
            for d in dirs {
                let npos = (pos.0+d.0, pos.1+d.1);
    
                if can_visit(&npos, &grid, &visited) && 
                    grid[npos.0 as usize][npos.1 as usize] as i32 - grid[pos.0 as usize][pos.1 as usize] as i32 == 1 {
                    q.push_back(npos);
                    visited.insert(npos);
                }
            }
        }
    }

    res
} 

fn part1(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let reader: BufReader<_> = BufReader::new(input);
    let grid: Vec<Vec<_>> = reader
        .lines()
        .map(|x| x
            .unwrap()
            .chars()
            .map(|y| y.to_digit(10).unwrap()).collect())
        .collect();

    let mut res = 0;
    for i in 0..grid.len() {
        for j in 0..grid[0].len() {
            if grid[i][j] == 0 {
                res += bfs(&grid, (i as i32, j as i32));
            }
        }
    }


    res
}

fn in_bounds(pos: &(i32,i32), grid: &Vec<Vec<u32>>) -> bool {
    pos.0 >= 0 && pos.1 >= 0 && 
    pos.0 < grid.len() as i32 && pos.1 < grid[0].len() as i32
}

fn bfs_uniq_paths(grid: &Vec<Vec<u32>>, src: (i32, i32)) -> i32 {
    let mut res = 0;
    let mut q: VecDeque<(i32,i32)> = VecDeque::new();

    q.push_front(src);

    let dirs = [(0,1),(0,-1),(1,0),(-1,0)];
    while !q.is_empty() {
        let pos = q.pop_front().unwrap();

        if grid[pos.0 as usize][pos.1 as usize] == 9 {
            res += 1;
        }   
        else {
            for d in dirs {
                let npos = (pos.0+d.0, pos.1+d.1);
    
                if in_bounds(&npos, grid) && 
                grid[npos.0 as usize][npos.1 as usize] as i32 - grid[pos.0 as usize][pos.1 as usize] as i32 == 1 {
                    q.push_back(npos);
                }
            }
        }
    }

    res
}

fn part2(filepath: &str) -> i32 {
    let input = File::open(filepath).unwrap();
    let reader: BufReader<_> = BufReader::new(input);
    let grid: Vec<Vec<_>> = reader
        .lines()
        .map(|x| x
            .unwrap()
            .chars()
            .map(|y| y.to_digit(10).unwrap()).collect())
        .collect();

    let mut res = 0;
    for i in 0..grid.len() {
        for j in 0..grid[0].len() {
            if grid[i][j] == 0 {
                res += bfs_uniq_paths(&grid, (i as i32, j as i32));
            }
        }
    }


    res
}

fn main() {
    assert_eq!(part1("src/day10/test.txt"),36);
    println!("Part 1: {}", part1("src/day10/input.txt"));

    assert_eq!(part2("src/day10/test.txt"),81);
    println!("Part 2: {}", part2("src/day10/input.txt"));
}