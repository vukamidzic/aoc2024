use std::{fs::File, io::{BufRead, BufReader}};
use std::collections::VecDeque;

fn can_achieve_target(target: &i64, nums: &Vec<i64>) -> bool {
    let mut queue: VecDeque<(i64,usize)> = VecDeque::new();
    queue.push_front((nums[0], 1));

    while !queue.is_empty() {
        let next = queue.pop_front().unwrap();

        if next.1 == nums.len() {
            if next.0 == *target { return true; }
            else { continue; }
        }

        queue.push_front((next.0 + nums[next.1], next.1+1));
        queue.push_front((next.0 * nums[next.1], next.1+1));
        // queue.push_front((format!("{}{}",next.0,nums[next.1]).parse().unwrap(), next.1+1)); 
    }

    false
}

fn solution(filepath: &str) -> i64 {
    let input = File::open(filepath).unwrap();
    let reader: BufReader<_> = BufReader::new(input);
    let data: Vec<_> = reader.lines().map(|x| x.unwrap()).collect();

    let mut res: i64 = 0;

    for line in data {
        let (target_str, nums_str) = line.split_once(':').unwrap();
        let target: i64 = target_str
            .trim()
            .parse()
            .unwrap();
        let nums: Vec<i64> = nums_str
            .trim()
            .split(' ')
            .map(|x| x.parse().unwrap())
            .collect();

        if can_achieve_target(&target, &nums) {
            res += target;
        }
    }


    res
}

fn main() {
    assert_eq!(solution("src/day7/test.txt"), 3749);
    println!("Part1 result: {}", solution("src/day7/input.txt"));

    // uncomment commented line in can_achieve_target() for part 2 to work
    assert_eq!(solution("src/day7/test.txt"), 11387);
    println!("Part2 result: {}", solution("src/day7/input.txt"));
}