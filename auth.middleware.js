const jwt = require("jsonwebtoken");
require("dotenv").config();



module.exports = (req,res,next)=>{
    // "Bearer 1a2b3ced5e"
    // ["Bearer" 1a2b3ced5e]
    if (!req.headers.authorization) return res.status(401).json({message: "Token no proporcionado"});
    const token = req.headers.authorization.split(" ")[1];
    if (!token) return res.status(401).json({message:"Token no proporcionado"});


    try {
        const decoded = jwt.verify(token, process.env.JWT_KEY);
        req.user = decoded;
        next();
    } catch (error) {
        res.status(401).json({message: error.message || "Token no valido"});
        
    }

}