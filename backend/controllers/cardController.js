const card = require("../models/cardModel");
const bcrypt = require("bcrypt");
const jwt = require("../config/jwt");

const getAll = (req, res) => {
  card.getAll((err, dbResult) => {
    if (err) {
      return res.status(500).send(err);
    }
    for (let i = 0; i < dbResult.length; i++) {
      delete dbResult[i].PIN;
    }
    res.json(dbResult);
  });
};

const deleteCard = (req, res) => {
  card.deleteCard(req.params.card_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "Card deleted" });
  });
};

const updateCard = (req, res) => {
  card.updateCard(req.body, req.params.card_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "Card updated" });
  });
};

const getById = (req, res) => {
  card.getById(req.params.card_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    delete dbResult[0].PIN;
    res.json(dbResult[0]);
  });
};

const addCard = (req, res) => {
  const cardData = req.body;
  if (!cardData.type || !cardData.pin) {
    return res.status(400).json({
      error: "Missing required fields",
    });
  }
  if (cardData.type != 0 && cardData.type != 1 && cardData.type != 2) {
    return res.status(400).json({
      error: "Invalid card type",
    });
  }
  bcrypt.hash(cardData.pin, 10, (err, hash) => {
    if (err) {
      return res.status(500).json({
        error: err,
      });
    } else {
      card.addCard(cardData, hash, (err, dbResult) => {
        if (err) {
          return res.status(500).json({
            error: err,
          });
        }
        return res.status(200).json({
          message: "Card created",
        });
      });
    }
  });
};

//login Pietarin tekemä!
const login = (req, res) => {
  card.getbyNumber(req.body.card_number, (err, results) => {
    if (err) {
      return res.status(500).json(err);
    }
    console.log(results[0].PIN.toString());

    bcrypt.compare(
      req.body.pin.toString(),
      results[0].PIN.toString(),
      (err, match) => {
        if (err) {
          return res.status(500).json(err);
        }
        if (match) {
          const account_id = results[0].account_id;
          const token = jwt.generateToken(results[0].card_id);
          return res.status(200).json({ status: "success", token: token,  account_id: account_id});
        } else {
          return res.status(400).json({ status: "invalid pin" });
        }
      }
    );
  });
};

module.exports = {
  getAll,
  getById,
  addCard,
  login,
  deleteCard,
  updateCard,
};
