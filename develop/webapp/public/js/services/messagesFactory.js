/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics (CRAG).
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
/**
 * Aquest factory agrupa funcions relacionades la sessió de l'usuari i les seves dades.
 */
CRAG.factory('MessagesFactory', function($modal) {
    return {
        
		/**
		 * Funció privada. Només la poden fer servir els mètodes d'aquest factory.
		 */	        
        private_message: function(message, title, type, list_values, callBackOk, callBackCancel) {
                        
            var form = $modal.open({
                templateUrl: 'partials/messagesFactory/message.html',
                controller: 'MessageController',
                backdrop: 'static',
                windowClass: 'app-modal-window',
				animation: true,
                resolve: {
                    type: function() {
                        return type;
                    },
                    title: function() {
                        return title;
                    },
                    message: function() {
                        return message;
                    },
                    list_values: function() {
                        return list_values;
                    }
                }
            });           
            

            form.result.then(
                    function(text) { if(callBackOk!=null) {callBackOk(text);} },
                    function() { if(callBackCancel!=null) {callBackCancel();} }
            );      
    
        },
        
		/**
		 * Aquesta funció mostra un missatge d'informació i l'usuari només pot acceptar-lo.
		 */	
        alert: function(message, callBackOk) {
            this.private_message(message, 'ngaSP', 'alert', null, callBackOk, null);
        },
        
		/**
		 * Aquesta funció mostra un missatge d'error i l'usuari només pot acceptar-lo.
		 */	
        error: function(message, callBackOk) {
            this.private_message(message, 'ngaSP', 'error', null, callBackOk, null);
        },
        
		/**
		 * Aquesta funció mostra un missatge d'error alhora que mostra un llistat i l'usuari només pot acceptar-lo.
		 */	
        errorList: function(message, list_values, callBackOk) {
            this.private_message(message, 'ngaSP', 'error', list_values, callBackOk, null);
        },
        
		/**
		 * Aquesta funció mostra una pregunta a l'usuari i aquest pot respodre Si o No.
		 */	
        confirm: function(message, callBackOk, callBackCancel) {
            this.private_message(message, 'ngaSP', 'confirm', null, callBackOk, callBackCancel);
        },        
        
		/**
		 * Aquesta funció mostra una pregunta a l'usuari alhora que li mostra un llistat.  L'usuari pot respodre Si o No.
		 */	
        confirmList: function(message, list_values, callBackOk, callBackCancel) {
            this.private_message(message, 'ngaSP', 'confirm', list_values, callBackOk, callBackCancel);
        },           

		/**
		 */	
        input: function(message, callBackOk, callBackCancel) {
            this.private_message(message, 'ngaSP', 'input', null, callBackOk, callBackCancel);
        },   
    };
});
