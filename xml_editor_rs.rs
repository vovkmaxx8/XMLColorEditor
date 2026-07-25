// xml_editor_rs.rs — редактор XML с цветовой схемой на Rust (консоль + termion)

use regex::Regex;
use std::fs;
use std::io::{self, Write, BufRead};
use termion::{color, style};

fn highlight_xml(text: &str) -> String {
    let mut result = text.to_string();
    // Теги
    let re = Regex::new(r"(<[^>]+>)").unwrap();
    result = re.replace_all(&result, |caps: &regex::Captures| {
        format!("{}{}{}", color::Fg(color::Green), &caps[0], style::Reset)
    }).to_string();
    // Атрибуты
    let re = Regex::new(r"\s+([a-zA-Z-]+)=").unwrap();
    result = re.replace_all(&result, |caps: &regex::Captures| {
        format!(" {}{}{}=", color::Fg(color::Yellow), &caps[1], style::Reset)
    }).to_string();
    // Значения
    let re = Regex::new(r#""[^"]*""#).unwrap();
    result = re.replace_all(&result, |caps: &regex::Captures| {
        format!("{}{}{}", color::Fg(color::Red), &caps[0], style::Reset)
    }).to_string();
    // Комментарии
    let re = Regex::new(r"<!--.*?-->").unwrap();
    result = re.replace_all(&result, |caps: &regex::Captures| {
        format!("{}{}{}", color::Fg(color::White), &caps[0], style::Reset)
    }).to_string();
    result
}

fn main() {
    println!("🎨 XMLColorEditor — Rust Edition");
    println!("Команды: open <file>, save, exit");
    let stdin = io::stdin();
    let mut reader = stdin.lock();
    let mut filename = String::new();
    let mut content = String::new();

    loop {
        print!("> ");
        io::stdout().flush().unwrap();
        let mut line = String::new();
        if reader.read_line(&mut line).is_err() { break; }
        let line = line.trim();
        let parts: Vec<&str> = line.splitn(2, ' ').collect();
        let cmd = parts[0];
        let arg = if parts.len() > 1 { parts[1] } else { "" };

        match cmd {
            "open" => {
                if arg.is_empty() {
                    println!("Укажите имя файла");
                    continue;
                }
                match fs::read_to_string(arg) {
                    Ok(data) => {
                        filename = arg.to_string();
                        content = data;
                        println!("✅ Открыт: {}", filename);
                        println!("{}", highlight_xml(&content));
                    }
                    Err(e) => println!("Ошибка: {}", e),
                }
            }
            "save" => {
                if filename.is_empty() {
                    println!("Нет открытого файла");
                    continue;
                }
                match fs::write(&filename, &content) {
                    Ok(()) => println!("✅ Сохранён: {}", filename),
                    Err(e) => println!("Ошибка сохранения: {}", e),
                }
            }
            "exit" => {
                println!("До свидания!");
                return;
            }
            _ => println!("Неизвестная команда"),
        }
    }
}
