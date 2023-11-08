import subprocess


def get_title_and_path(line: str) -> tuple[str, str]:
    check_index = len("-   [x] ")

    line = line[check_index:]

    start = line.find("[") + 1
    end = line.find("]")

    title = line[start:end]

    start = line.find("(") + 1
    end = line.find(")")

    filepath = line[start:end]

    return (title, filepath)


def add_title(filepath: str, title: str):
    with open(filepath, "r") as file:
        content = file.read()

        if not content[0] == "#":
            with open(filepath, "w") as write_file:
                content = "# " + title + "\n\n" + content
                write_file.write(content)

        return content


def handle_line(line: str):
    if line.find("[x]") == -1:
        return ""

    (title, filepath) = get_title_and_path(line)

    content = add_title(filepath, title)

    return content


with open("./Checklist.md", "r") as file:
    all_content = ""
    for line in file:
        content = handle_line(line)
        if not content == "":
            all_content += content + "\n\\newpage\n\n"

    with open("out.md", "w") as write_file:
        write_file.write(all_content)
