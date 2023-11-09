const user = require("../models/userModel");

const getAll = (req, res) => {
  user.getAll((err, dbResult) => {
    if (err) {
      return res.status(500).send(err);
    }
    res.json(dbResult);
  });
};

const getById = (req, res) => {
  user.getById(req.params.user_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.json(dbResult[0]);
  });
};

const createUser = (req, res) => {
  user.createUser(req.body, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "User created" });
  });
};

const deleteUser = (req, res) => {
  user.deleteUser(req.params.user_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "User deleted" });
  });
};

const updateUser = (req, res) => {
  user.updateUser(req.body, req.params.user_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "User updated" });
  });
};

module.exports = {
  getAll,
  getById,
  createUser,
  deleteUser,
  updateUser,
};
