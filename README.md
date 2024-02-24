<p align="center">
  <a href="https://github.com/swiftly-solution/swiftly_mostactive">
    <img src="https://cdn.swiftlycs2.net/swiftly-logo.png" alt="SwiftlyLogo" width="80" height="80">
  </a>

  <h3 align="center">[Swiftly] Most Active</h3>

  <p align="center">
    A simple plugin for Swiftly that saves the connected time of a player on server in database.
    <br/>
  </p>
</p>

<p align="center">
  <img src="https://img.shields.io/github/downloads/swiftly-solution/swiftly_mostactive/total" alt="Downloads"> 
  <img src="https://img.shields.io/github/contributors/swiftly-solution/swiftly_mostactive?color=dark-green" alt="Contributors">
  <img src="https://img.shields.io/github/issues/swiftly-solution/swiftly_mostactive" alt="Issues">
  <img src="https://img.shields.io/github/license/swiftly-solution/swiftly_mostactive" alt="License">
</p>

---

### Installation 👀

1. Download the newest [release](https://github.com/swiftly-solution/swiftly_mostactive/releases).
2. Everything is drag & drop, so i think you can do it!
3. Setup database connection in `addons/swiftly/configs/databases.json` with the key `swiftly_mostactive` like in the following example:
```json
{
    "swiftly_mostactive": {
        "hostname": "...",
        "username": "...",
        "password": "...",
        "database": "...",
        "port": 3306
    }
}
```
> [!WARNING]
> Don't forget to replace the `...` with the actual values !!

### Configuring the plugin 🧐

* After installing the plugin, you need to change the prefix and the `hours` command name from `addons/swiftly/configs/plugins` and if you want, you can change the messages from `addons/swiftly/translations`.

### Creating A Pull Request 😃

1. Fork the Project
2. Create your Feature Branch
3. Commit your Changes
4. Push to the Branch
5. Open a Pull Request

### Have ideas/Found bugs? 💡
Join [Swiftly Discord Server](https://swiftlycs2.net/discord) and send a message in the topic from `📕╎plugins-sharing` of this plugin!

---
