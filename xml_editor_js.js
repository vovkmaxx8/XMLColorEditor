// xml_editor_js.js — редактор XML с цветовой схемой на JavaScript (Node.js)

const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: '> '
});

const RESET = '\x1b[0m';
const GREEN = '\x1b[32m';
const YELLOW = '\x1b[33m';
const RED = '\x1b[31m';
const GRAY = '\x1b[37m';

function highlightXML(text) {
    // Теги
    text = text.replace(/(<[^>]+>)/g, GREEN + '$1' + RESET);
    // Атрибуты
    text = text.replace(/\s+([a-zA-Z-]+)=/g, ' ' + YELLOW + '$1' + RESET + '=');
    // Значения
    text = text.replace(/"[^"]*"/g, RED + '$&' + RESET);
    // Комментарии
    text = text.replace(/<!--.*?-->/g, GRAY + '$&' + RESET);
    return text;
}

let filename = '';
let content = '';

console.log('🎨 XMLColorEditor — JavaScript Edition');
console.log('Команды: open <file>, save, exit');
rl.prompt();

rl.on('line', (line) => {
    const parts = line.trim().split(' ');
    const cmd = parts[0];
    const arg = parts.slice(1).join(' ');
    switch (cmd) {
        case 'open':
            if (!arg) {
                console.log('Укажите имя файла');
                break;
            }
            try {
                content = fs.readFileSync(arg, 'utf8');
                filename = arg;
                console.log('✅ Открыт:', filename);
                console.log(highlightXML(content));
            } catch (e) {
                console.log('Ошибка:', e.message);
            }
            break;
        case 'save':
            if (!filename) {
                console.log('Нет открытого файла');
                break;
            }
            try {
                fs.writeFileSync(filename, content);
                console.log('✅ Сохранён:', filename);
            } catch (e) {
                console.log('Ошибка сохранения:', e.message);
            }
            break;
        case 'exit':
            console.log('До свидания!');
            rl.close();
            return;
        default:
            console.log('Неизвестная команда');
    }
    rl.prompt();
}).on('close', () => process.exit(0));
