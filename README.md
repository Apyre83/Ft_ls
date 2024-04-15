# ft_ls

## Introduction
`ft_ls` is a custom implementation of the classic Unix `ls` command, built using C. This project aims to replicate the functionality of `ls`, which lists directory contents and provides various options for how these contents are displayed.

## Table of Contents
- [Installation](#installation)
- [Features](#features)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

To install `ft_ls`, clone this repository and compile the source files using Make:

```bash
git clone https://github.com/yourusername/ft_ls.git
cd ft_ls
make
```

This will create an executable named `ft_ls` that you can run to use the custom `ls` command.

## Features

`ft_ls` supports several options that modify its behavior:

- `-l` : List in long format.
- `-R` : Recursively list subdirectories encountered.
- `-a` : Include directory entries whose names begin with a dot (`.`).
- `-r` : Reverse the order of the sort to get reverse lexicographical order or the oldest entries first.
- `-t` : Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.

## Usage

To use `ft_ls`, you can simply run the executable followed by any options you need. Here are some examples:

```bash
./ft_ls -l
./ft_ls -R
./ft_ls -a
./ft_ls -r
./ft_ls -t
```

You can also combine different options:

```bash
./ft_ls -laR
```

## Contributing

Contributions to `ft_ls` are welcome! Please feel free to fork the repository, make changes, and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

## License

Distributed under the MIT License. See `LICENSE` for more information.