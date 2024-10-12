# MelodyMiner

**MelodyMiner** is a music database project designed to mine and manage MP3 files with ID3v2.4 tags. The application features a user-friendly graphical interface that displays song information (such as title, artist, album, and cover art) and allows users to perform queries using an easy-to-understand language.


---

### **Attention:** 

**When the program is run, an additional window is created.** 

**Do not close this window; it is a bug that I am currently working on.**

---


## Key Features

- Automatically scans a specified directory for MP3 files and extracts relevant metadata, including:
  - Performer
  - Title
  - Album
  - Recording year
  - Genre
  - Track number
- Stores data in a structured database with predefined tables for performers, albums, and songs.
- Allows users to:
  - View song and album details
  - Query songs by title, artist, or album.

This project aims to simplify the management of music collections while providing insightful metadata at the user’s fingertips.


## **Installation of Dependencies**

Before running the project, make sure to install the following dependencies:

- **TagLib**
- **GTKmm 4**
- **GoogleTest**
- **Meson**

You can install them using your system's package manager. For example, on Ubuntu, you can use:

```bash
sudo apt install libtag1-dev libgtkmm-4.0-dev libgtest-dev meson
```

Ensure that the libraries are correctly installed on your system.

## **Build and Run**

1. Clone the repository:
   ```bash
   git clone https://github.com/WendySC25/melodyMiner.git
   cd melodyMiner
   ```

2. Set up the project using Meson:
   ```bash
   meson setup builddir
   ```

3. Compile the project:
   ```bash
   meson compile -C builddir
   ```

4. Run the application:
   ```bash
   ./builddir/melodyMiner
   ```

## **Testing**

To run the tests, make sure you have GoogleTest installed, and then run:

```bash
meson test -C builddir
```

## **Performing Searches**

In MelodyMiner, you can perform searches using a specific query syntax to filter songs based on various criteria. Below are the types of queries you can use, along with examples.

### **Query Syntax**

The general format for queries is:

- **title[<value>]**: Searches for songs with titles matching the specified value.
- **album[<value>]**: Searches for songs from albums matching the specified value.
- **performer[<value>]**: Searches for songs by performers matching the specified value.
- **year[<value>]**: Searches for songs from a specific year.
- **genre[<value>]**: Searches for songs of a specific genre.
- **track[<number>]**: Searches for songs with a specific track number.

You can combine multiple queries using commas, and you can use the following operators within square brackets:
- `|` for logical OR
- `&` for logical AND

### **Examples**

1. **Title Queries**
   - Search for songs with "love" in the title:
     ```
     title[love]
     ```
     SQL Equivalent: `SELECT * FROM rolas r WHERE (r.title LIKE '%love%');`

   - Search for songs with either "love" or "happy" in the title:
     ```
     title[love|happy]
     ```
     SQL Equivalent: `SELECT * FROM rolas r WHERE (r.title LIKE '%love%' OR r.title LIKE '%happy%');`

   - Search for songs that have both "love" and "happy" in the title:
     ```
     title[love&happy]
     ```
     SQL Equivalent: `SELECT * FROM rolas r WHERE (r.title LIKE '%love%' AND r.title LIKE '%happy%');`

2. **Album Queries**
   - Search for songs from an album named "a":
     ```
     album[a]
     ```
     SQL Equivalent: `SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album WHERE (a.name LIKE '%a%');`

   - Search for albums "a" or "b":
     ```
     album[a|b]
     ```
     SQL Equivalent: `SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album WHERE (a.name LIKE '%a%' OR a.name LIKE '%b%');`

3. **Performer Queries**
   - Search for songs by performer "John Doe":
     ```
     performer[John Doe]
     ```
     SQL Equivalent: `SELECT * FROM rolas r JOIN performers p ON r.id_performer = p.id_performer WHERE (p.name LIKE '%John Doe%');`

   - Search for performers "fire" or "Jane Doe":
     ```
     performer[fire|Jane Doe]
     ```
     SQL Equivalent: `SELECT * FROM rolas r JOIN performers p ON r.id_performer = p.id_performer WHERE (p.name LIKE '%fire%' OR p.name LIKE '%Jane Doe%');`

4. **Year Queries**
   - Search for songs from the year 2024:
     ```
     year[2024]
     ```
     SQL Equivalent: `SELECT * FROM rolas r WHERE (r.year = 2024);`

5. **Combined Queries**
   - Search for songs with multiple criteria:
     ```
     title[love], album[a], performer[John Doe], year[2022], genre[pop], track[1]
     ```
     SQL Equivalent:
     ```
     SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album 
     JOIN performers p ON r.id_performer = p.id_performer 
     WHERE (r.title LIKE '%love%') AND (a.name LIKE '%a%') AND 
     (p.name LIKE '%John Doe%') AND (r.year = 2022) AND 
     (r.genre LIKE '%pop%') AND (r.track = 1);
     ```

By using the above query syntax and examples, you can effectively search for songs within the MelodyMiner application.


# **Important Notice**

**This project is in development.**

**Don't forget to check the wiki!** I have added a couple of documents.
