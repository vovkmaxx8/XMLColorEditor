// xml_editor_go.go — редактор XML с цветовой схемой на Go (консоль + ANSI)

package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"regexp"
	"strings"
)

const (
	reset  = "\033[0m"
	green  = "\033[32m"
	yellow = "\033[33m"
	red    = "\033[31m"
	gray   = "\033[37m"
	white  = "\033[97m"
)

func highlightXML(text string) string {
	// Теги
	re := regexp.MustCompile(`(<[^>]+>)`)
	text = re.ReplaceAllString(text, green+"$1"+reset)
	// Атрибуты
	re = regexp.MustCompile(`\s+([a-zA-Z-]+)=`)
	text = re.ReplaceAllString(text, " "+yellow+"$1"+reset+"=")
	// Значения
	re = regexp.MustCompile(`"[^"]*"`)
	text = re.ReplaceAllString(text, red+"$0"+reset)
	// Комментарии
	re = regexp.MustCompile(`<!--.*?-->`)
	text = re.ReplaceAllString(text, gray+"$0"+reset)
	return text
}

func main() {
	fmt.Println("🎨 XMLColorEditor — Go Edition")
	fmt.Println("Команды: open <file>, save, exit")
	scanner := bufio.NewScanner(os.Stdin)
	var filename string
	var content string

	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		parts := strings.SplitN(line, " ", 2)
		cmd := parts[0]
		arg := ""
		if len(parts) > 1 {
			arg = parts[1]
		}
		switch cmd {
		case "open":
			if arg == "" {
				fmt.Println("Укажите имя файла")
				continue
			}
			data, err := ioutil.ReadFile(arg)
			if err != nil {
				fmt.Println("Ошибка:", err)
				continue
			}
			filename = arg
			content = string(data)
			fmt.Println("✅ Открыт:", filename)
			fmt.Println(highlightXML(content))
		case "save":
			if filename == "" {
				fmt.Println("Нет открытого файла")
				continue
			}
			err := ioutil.WriteFile(filename, []byte(content), 0644)
			if err != nil {
				fmt.Println("Ошибка сохранения:", err)
			} else {
				fmt.Println("✅ Сохранён:", filename)
			}
		case "exit":
			fmt.Println("До свидания!")
			return
		default:
			fmt.Println("Неизвестная команда")
		}
	}
}
