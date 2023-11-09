const database = require("../config/database");

const user = {
  getAll: function (callback) {
    return database.query("SELECT * FROM users", callback);
  },
  getById: function (user_id, callback) {
    return database.query(
      "SELECT * FROM users WHERE user_id = ?",
      [user_id],
      callback
    );
  },
  createUser: function (data, callback) {
    return database.query(
      "INSERT INTO users (fname, lname) VALUES (?, ?)",
      [data.fname, data.lname],
      callback
    );
  },
  deleteUser: function (user_id, callback) {
    return database.query(
      "DELETE FROM users WHERE user_id = ?",
      [user_id],
      callback
    );
  },

  updateUser: function (data, user_id, callback) {
    return database.query(
      "UPDATE users SET fname = ?, lname = ? WHERE user_id = ?",
      [data.fname, data.lname, user_id],
      callback
    );
  },
};

module.exports = user;
